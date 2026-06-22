#include "FitnessGoal.h"

FitnessGoal::FitnessGoal(GoalType goalType, double targetValue, time_t deadline)
    : _goalType(goalType)
    , _targetValue(targetValue)
    , _startDate(std::time(nullptr))
    , _deadline(deadline)
    , _isAchieved(false) { }

FitnessGoal::FitnessGoal(GoalType goalType, double targetValue, time_t startDate, time_t deadline, bool isAchieved)
    : _goalType(goalType)
    , _targetValue(targetValue)
    , _startDate(startDate)
    , _deadline(deadline)
    , _isAchieved(isAchieved) {
}

GoalType FitnessGoal::getGoalType() const {
    return _goalType;
}

double FitnessGoal::getTargetValue() const {
    return _targetValue;
}

time_t FitnessGoal::getStartDate() const {
    return _startDate;
}

time_t FitnessGoal::getDeadline() const {
    return _deadline;
}

bool FitnessGoal::getIsAchieved() const {
    return _isAchieved;
}