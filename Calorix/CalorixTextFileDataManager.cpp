#include "CalorixTextFileDataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    Section currentState = Section::None;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line.find("---") == 0) continue;

        if (line == "Users:") { currentState = Section::Users; continue; }
        if (line == "Food:") { currentState = Section::Food; continue; }
        if (line == "Exercises:") { currentState = Section::Exercises; continue; }

        std::vector<std::string> tokens = split(line, "|");

        try {
            switch (currentState) {
            case Section::Users:
                //Implement for users
                break;

            case Section::Food:
                //Implement for food
                break;

            case Section::Exercises:
                //Implement for exercises
                break;

            case Section::None:
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
        }
    }
}

void CalorixTextFileDataManager::saveToFile(const std::string& filename, const Calorix& system) {

}
