#include "FitnessGoal.h"

GoalType FitnessGoal::getGoalType() const {
    return _goalType;
}

double FitnessGoal::getTargetValue() const {
    return _targetValue;
}

FitnessGoal::FitnessGoal(GoalType goalType, double targetValue, time_t deadline)
    : _goalType(goalType)
    , _targetValue(targetValue)
    , _startDate(std::time(nullptr))
    , _deadline(deadline)
    , isAchieved(false) { }