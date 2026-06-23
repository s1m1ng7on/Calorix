#include "CalorixHelper.h"
#include <chrono>
#include <format>
#include <stdexcept>
#include "UserProfile.h"
#include "FitnessGoal.h"

bool CalorixHelper::isToday(const time_t& entryTimeStamp) {
    auto current_zone = std::chrono::current_zone();
    auto current_day = current_zone->to_local(std::chrono::system_clock::now());
    auto entry_day = current_zone->to_local(std::chrono::system_clock::from_time_t(entryTimeStamp));

    return std::chrono::floor<std::chrono::days>(current_day) == std::chrono::floor<std::chrono::days>(entry_day);
}

Gender CalorixHelper::parseGenderStr(const std::string& genderStr) {
    if (genderStr == "Male")
        return Gender::Male;

    if (genderStr == "Female")
        return Gender::Female;

    throw std::invalid_argument("Invalid gender string.");
}

ActivityLevel CalorixHelper::parseActivityLevelStr(const std::string& activityStr) {
    if (activityStr == "Sedentary")
        return ActivityLevel::Sedentary;

    if (activityStr == "Light")
        return ActivityLevel::Light;

    if (activityStr == "Moderate")
        return ActivityLevel::Moderate;

    if (activityStr == "Active")
        return ActivityLevel::Active;

    if (activityStr == "VeryActive")
        return ActivityLevel::VeryActive;

    throw std::invalid_argument(std::format("Unknown ActivityLevel string: {}", activityStr));
}

GoalType CalorixHelper::parseGoalStr(const std::string& goalTypeStr) {
    if (goalTypeStr == "WeightLoss")
        return GoalType::WeightLoss;

    if (goalTypeStr == "Bulking")
        return GoalType::Bulking;

    if (goalTypeStr == "Maintenance")
        return GoalType::Maintenance;

    throw std::invalid_argument(std::format("Unknown GoalType string: {}", goalTypeStr));
}

TargetType CalorixHelper::parseTargetTypeStr(const std::string& targetTypeStr) {
    if (targetTypeStr == "Weight")
        return TargetType::Weight;

    if (targetTypeStr == "Calories")
        return TargetType::Calories;

    throw std::invalid_argument(std::format("Unknown TargetType string: {}", targetTypeStr));
}

std::string CalorixHelper::parseGender(Gender gender) {
    switch (gender) {
    case Gender::Male:
        return "Male";
    case Gender::Female:
        return "Female";
    }

    throw std::logic_error("Unhandled TargetType enum value");
}

std::string CalorixHelper::parseActivityLevel(ActivityLevel activityLevel) {
    switch (activityLevel) {
    case ActivityLevel::Sedentary:
        return "Sedentary";
    case ActivityLevel::Light:
        return "Light";
    case ActivityLevel::Moderate:
        return "Moderate";
    case ActivityLevel::Active:
            return "Active";
    case ActivityLevel::VeryActive:
        return "VeryActive";
    }

    throw std::logic_error("Unhandled ActivityLevel enum value");
}

std::string CalorixHelper::parseTargetType(TargetType targetType) {
    switch (targetType) {
    case TargetType::Weight:
        return "Weight";
    case TargetType::Calories:
        return "Calories";
    }

    throw std::logic_error("Unhandled TargetType enum value");
}

std::string CalorixHelper::parseGoal(GoalType goalType) {
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
