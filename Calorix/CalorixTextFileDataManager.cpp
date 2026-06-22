#include "CalorixTextFileDataManager.h"
#include <fstream>
#include <iostream>
#include "Calorix.h"

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

Gender CalorixTextFileDataManager::parseGender(const std::string& genderStr) {
    if (genderStr == "Male")
        return Gender::Male;

    if (genderStr == "Female")
        return Gender::Female;

    throw std::invalid_argument("Invalid gender string.");
}

GoalType CalorixTextFileDataManager::parseGoalStr(const std::string& goalTypeStr) {
    if (goalTypeStr == "WeightLoss")
        return GoalType::WeightLoss;

    if (goalTypeStr == "Bulking")
        return GoalType::Bulking;

    if (goalTypeStr == "Maintenance")
        return GoalType::Maintenance;

    throw std::invalid_argument(std::format("Unknown GoalType string: {}", goalTypeStr));
}

std::string CalorixTextFileDataManager::parseGoal(GoalType goalType) {
    switch (goalType) {
    case GoalType::WeightLoss:
        return "WeightLoss";
    case GoalType::Bulking:
        return "Bulking";
    case GoalType::Maintenance:
        return "Maintenance";
    }

    throw std::logic_error("Unhandled GoalType enum value");
}

void CalorixTextFileDataManager::loadFromFile(const std::string& filename, Calorix& calorix) {
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error(std::format("Could not open file : {}.", filename));

    std::string line;
    Section currentState = Section::None;
    UserSubsection currentSubsection = UserSubsection::None;
    Trainee* currentTrainee = nullptr;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line == "---" || line.find("----------------") == 0)
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
                calorix.addFoodInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
                break;

            case Section::Exercises:
                calorix.addExerciseInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), tokens[3]);
                break;

            case Section::Users:
                if (line.find("Goals:") == 0) {
                    if (currentTrainee) {
                        std::string goalTypeStr = trim(tokens[0].substr(std::string("Goals:").length()));
                        GoalType type = CalorixTextFileDataManager::parseGoalStr(goalTypeStr);
                        double targetValue = std::stod(tokens[1]);
                        time_t deadline = static_cast<time_t>(std::stoll(tokens[3]));

                        currentTrainee->setGoals(type, targetValue, deadline);
                    }
                }
                else if (currentSubsection == UserSubsection::FoodDiary) {
                    if (currentTrainee)
                        currentTrainee->logFood(tokens[0], std::stoi(tokens[1]));
                }
                else if (currentSubsection == UserSubsection::ExerciseDiary) {
                    if (currentTrainee)
                        currentTrainee->logExercise(tokens[0], std::stoi(tokens[1]));
                }
                else if (currentSubsection == UserSubsection::FavoriteExercises) {
                    if (currentTrainee)
                        currentTrainee->addToFavorites(line);
                }
                else {
                    currentSubsection = UserSubsection::None;
                    currentTrainee = nullptr;

                    bool isAdmin = (tokens.size() > 6 && tokens[6] == "Admin");

                    User* rawUser = calorix.addUserInternal(tokens[0], tokens[1], std::stoi(tokens[2]), std::stod(tokens[3]), std::stoi(tokens[4]), parseGender(tokens[5]), isAdmin);

                    if (!isAdmin)
                        currentTrainee = dynamic_cast<Trainee*>(rawUser);
                }
                break;

            case Section::None:
                break;
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
            << ((user->_profile->getGender() == Gender::Male) ? "Male" : "Female")
            << (user->isAdmin() ? " | Admin" : "") << "\n";


        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());
        if (trainee) {
            const FitnessGoal& goal = trainee->getGoal();

            file
                << "Goals: "
                << CalorixTextFileDataManager::parseGoal(goal.getGoalType()) << " | "
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
