#include "CalorixTextFileDataManager.h"
#include <fstream>
#include <iostream>
#include "Calorix.h"

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

void CalorixTextFileDataManager::loadFromFile(const std::string& filename, Calorix& calorix) {
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error(std::format("Could not open file : {}.", filename));

    std::string line;
    Section currentState = Section::None;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line.find("---") == 0)
            continue;

        if (line == "Users:") {
            currentState = Section::Users;
            continue;
        }

        if (line == "Food:") {
            currentState = Section::Food;
            continue;
        }

        if (line == "Exercises:") {
            currentState = Section::Exercises;
            continue;
        }

        std::vector<std::string> tokens = split(line, "|");

        try {
            switch (currentState) {
            case Section::Users:
                calorix.addUserInternal(tokens[0], tokens[1], std::stoi(tokens[2]), std::stod(tokens[3]), std::stoi(tokens[4]), parseGender(tokens[5]));
                break;
            case Section::Food:
                calorix.addFoodInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
                break;
            case Section::Exercises:
                calorix.addExerciseInternal(tokens[0], std::stoi(tokens[1]), std::stoi(tokens[2]), static_cast<MuscleGroup>(std::stoi(tokens[3])));
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

    const std::string sectionDivider = "-------------------------------------------------\n";

    file << "Users:" << "\n";
    for (const auto& user : calorix._users) {
        file
            << user->getUsername() << " | "
            << user->_password << " | "
            << user->_profile->getAge() << " | "
            << user->_profile->getWeight() << " | "
            << user->_profile->getHeight() << " | "
            << ((user->_profile->getGender() == Gender::Male) ? "Male" : "Female") << "\n";
    }

    file << sectionDivider;

    file << "Food:" << "\n";
    for (const auto& food : calorix._foods) {
        file
            << food->getName() << " | "
            << food->getCaloriesPer100g() << " | "
            << food->getProteinPer100g() << " | "
            << food->getCarbsPer100g() << " | "
            << food->getFatPer100g() << "\n";
    }

    file << sectionDivider;

    file << "Exercises:" << "\n";
    for (const auto& exercise : calorix._exercises) {
        file
            << exercise->getName() << " | "
            << exercise->getCaloriesBurnedPerHour() << " | "
            << exercise->getSuggestedDuration() << " | "
            << static_cast<int>(exercise->getMuscleGroup()) << "\n";
    }

    file.close();
}
