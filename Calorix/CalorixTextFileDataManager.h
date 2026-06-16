#pragma once
#include <string>
#include <vector>
#include "Calorix.h"

class CalorixTextFileDataManager {
private:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    enum class Section {
        None,
        Users,
        Food,
        Exercises
    };
public:
    static void loadFromFile(const std::string& filename, Calorix& system);
    static void saveToFile(const std::string& filename, const Calorix& system);
};

