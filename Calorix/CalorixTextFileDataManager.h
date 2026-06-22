#pragma once
#include <string>
#include <vector>
#include "User.h"
#include "Trainee.h"

class Calorix;

class CalorixTextFileDataManager {
private:
    static const std::string _sectionDivider;
    static const std::string _smallDivider;

    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    static Gender parseGender(const std::string& genderStr);
    static GoalType parseGoalStr(const std::string& goalTypeStr);
    static std::string parseGoal(GoalType goalType);

    enum class Section {
        None,
        Users,
        Food,
        Exercises
    };

    enum class UserSubsection {
        None,
        FoodDiary,
        ExerciseDiary,
        FavoriteExercises
    };
public:
    static void loadFromFile(const std::string& filename, Calorix& calorix);
    static void saveToFile(const std::string& filename, const Calorix& calorix);
};
