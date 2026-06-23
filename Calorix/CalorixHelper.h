#pragma once
#include <ctime>
#include <string>

enum class Gender;
enum class GoalType;
enum class TargetType;
enum class ActivityLevel;

class CalorixHelper
{
public:
    static bool isToday(const time_t& entryTimeStamp);

    static Gender parseGenderStr(const std::string& genderStr);
    static ActivityLevel parseActivityLevelStr(const std::string& activityLevelStr);
    static GoalType parseGoalStr(const std::string& goalTypeStr);
    static TargetType parseTargetTypeStr(const std::string& targetTypeStr);

    static std::string parseGender(Gender gender);
    static std::string parseActivityLevel(ActivityLevel activityLevel);
    static std::string parseTargetType(TargetType targetType);
    static std::string parseGoal(GoalType goalType);
};