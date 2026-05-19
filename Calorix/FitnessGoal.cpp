#include "FitnessGoal.h"

FitnessGoal::FitnessGoal(GoalType goalType, double targetValue, time_t deadline)
    : _goalType(goalType)
    , _targetValue(targetValue)
    , _startDate(std::time(nullptr))
    , _deadline(deadline)
    , isAchieved(false) { }