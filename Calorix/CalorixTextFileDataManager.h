#pragma once
#include <string>
#include <vector>
#include "User.h"

class Calorix;

class CalorixTextFileDataManager {
private:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    static Gender parseGender(const std::string& genderStr);

    enum class Section {
        None,
        Users,
        Food,
        Exercises
    };
public:
    static void loadFromFile(const std::string& filename, Calorix& calorix);
    static void saveToFile(const std::string& filename, const Calorix& calorix);
};
