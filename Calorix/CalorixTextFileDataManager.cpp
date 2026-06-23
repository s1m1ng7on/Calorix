#include "CalorixTextFileDataManager.h"
#include <fstream>
#include <iostream>
#include "Calorix.h"
#include "CalorixHelper.h"

const std::string CalorixTextFileDataManager::_sectionDivider = "-------------------------------------------------\n";
const std::string CalorixTextFileDataManager::_smallDivider = "---\n";;

std::string CalorixTextFileDataManager::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> CalorixTextFileDataManager::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(trim(str.substr(start, end - start)));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(trim(str.substr(start)));
    return tokens;
}

void CalorixTextFileDataManager::loadFromFile(const std::string& filename, Calorix& calorix) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << std::format("Warning: Could not open file: {}. Starting with an empty state. File will be created upon exit.", filename) << std::endl;
        return;
    }

    std::string line;
    Section currentState = Section::None;
    UserSubsection currentSubsection = UserSubsection::None;
    Trainee* currentTrainee = nullptr;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line.find("---") == 0)
            continue;

        if (line == "Food:") {
            currentState = Section::Food;
            continue;
        }

        if (line == "Exercises:") {
            currentState = Section::Exercises;
            continue;
        }

        if (line == "Users:") {
            currentState = Section::Users;
            currentSubsection = UserSubsection::None;
            currentTrainee = nullptr;
            continue;
        }

        if (currentState == Section::Users) {
            if (line == "FoodDiary:") {
                currentSubsection = UserSubsection::FoodDiary;
                continue;
            }

            if (line == "ExerciseDiary:") {
                currentSubsection = UserSubsection::ExerciseDiary;
                continue;
            }

            if (line == "FavoriteExercises:") {
                currentSubsection = UserSubsection::FavoriteExercises;
                continue;
            }
        }

        std::vector<std::string> tokens = split(line, "|");
        try {
            switch (currentState) {
            case Section::Food:
                if (tokens.size() >= 5)
                    calorix.addFoodInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
                break;
            case Section::Exercises:
                if (tokens.size() >= 4)
                    calorix.addExerciseInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), tokens[3]);
                break;
            case Section::Users:
                if (tokens.size() >= 7 && (tokens[5] == "Male" || tokens[5] == "Female")) {
                    currentSubsection = UserSubsection::None;
                    bool isAdmin = (tokens.size() >= 8 && trim(tokens[7]) == "Admin");
                    User* rawUser = calorix.addUserInternal(tokens[0], tokens[1], std::stoi(tokens[2]), std::stod(tokens[3]), std::stoi(tokens[4]), CalorixHelper::parseGenderStr(tokens[5]), CalorixHelper::parseActivityLevelStr(tokens[6]), isAdmin);
                    currentTrainee = isAdmin ? nullptr : dynamic_cast<Trainee*>(rawUser);
                }
                else if (line.find("Goals:") == 0) {
                    if (currentTrainee && tokens.size() >= 5) {
                        std::string goalTypeStr = trim(tokens[0].substr(6));
                        currentTrainee->setGoals(CalorixHelper::parseGoalStr(goalTypeStr), CalorixHelper::parseTargetTypeStr(tokens[1]), std::stod(tokens[2]), static_cast<time_t>(std::stoll(tokens[4])));
                    }
                }
                else if (currentSubsection == UserSubsection::FoodDiary) {
                    if (currentTrainee && tokens.size() >= 2)
                        currentTrainee->logFood(tokens[0], std::stoi(tokens[1]));
                }
                else if (currentSubsection == UserSubsection::ExerciseDiary) {
                    if (currentTrainee && tokens.size() >= 2)
                        currentTrainee->logExercise(tokens[0], std::stoi(tokens[1]));
                }
                else if (currentSubsection == UserSubsection::FavoriteExercises) {
                    if (currentTrainee)
                        currentTrainee->addToFavorites(line);
                }
                break;
            case Section::None: break;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error parsing line: " << line << " - " << e.what() << std::endl;
        }
    }
}

void CalorixTextFileDataManager::saveToFile(const std::string& filename, const Calorix& calorix) {
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error(std::format("Could not open file : {}.", filename));

    file << "Food:" << "\n";
    for (int i = 0; i < calorix._foods.size(); i++) {
        const auto& food = calorix._foods[i];
        file
            << food->getName() << " | "
            << food->getCaloriesPer100g() << " | "
            << food->getProteinPer100g() << " | "
            << food->getCarbsPer100g() << " | "
            << food->getFatPer100g() << "\n";

        if (i < calorix._foods.size() - 1)
            file << _smallDivider;
    }

    file << _sectionDivider;

    file << "Exercises:" << "\n";
    for (int i = 0; i < calorix._exercises.size(); i++) {
        const auto& exercise = calorix._exercises[i];
        file
            << exercise->getName() << " | "
            << exercise->getCaloriesBurnedPerHour() << " | "
            << exercise->getSuggestedDuration() << " | "
            << exercise->getMuscleGroup() << "\n";

        if (i < calorix._exercises.size() - 1)
            file << _smallDivider;
    }

    file << _sectionDivider;

    file << "Users:" << "\n";
    for (int i = 0; i < calorix._users.size(); i++) {
        const auto& user = calorix._users[i];

        file
            << user->getUsername() << " | "
            << user->_password << " | "
            << user->_profile->getAge() << " | "
            << user->_profile->getWeight() << " | "
            << user->_profile->getHeight() << " | "
            << CalorixHelper::parseGender(user->_profile->getGender()) << " | "
            << CalorixHelper::parseActivityLevel(user->_profile->getActivityLevel())
            << (user->isAdmin() ? " | Admin" : "") << "\n";


        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());
        if (trainee) {
            const FitnessGoal& goal = trainee->getGoal();

            file
                << "Goals: "
                << CalorixHelper::parseGoal(goal.getGoalType()) << " | "
                << CalorixHelper::parseTargetType(goal.getTargetType()) << " | "
                << goal.getTargetValue() << " | "
                << (long long)goal.getStartDate() << " | "
                << (long long)goal.getDeadline() << " | "
                << goal.getIsAchieved() << "\n";

            const auto& foodDiary = trainee->getFoodDiary();
            if (!foodDiary.empty()) {
                file << "FoodDiary:\n";
                for (const auto& food : foodDiary) {
                    file
                        << food.getFoodName() << " | "
                        << food.getQuantityGrams() << " | "
                        << (long long)food.getDate() << "\n";
                }
            }

            const auto& exerciseDiary = trainee->getExerciseDiary();
            if (!exerciseDiary.empty()) {
                file << "ExerciseDiary:\n";
                for (const auto& exercise : exerciseDiary) {
                    file
                        << exercise.getExerciseName() << " | "
                        << exercise.getDurationMinutes() << " | "
                        << (long long)exercise.getDate() << "\n";
                }
            }

            const auto& favoriteExercises = trainee->getFavoriteExercises();
            if (!favoriteExercises.empty()) {
                file << "FavoriteExercises:\n";
                for (const auto& exercise : favoriteExercises) {
                    file << exercise->getName() << "\n";
                }
            }
        }

        if (i < calorix._users.size() - 1)
            file << _smallDivider;
    }

    file.close();
}
