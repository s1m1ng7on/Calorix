#pragma once
#include <ctime>

enum class GoalType {
	WeightLoss,
	Bulking,
	Maintenance
};

class FitnessGoal
{
private:
	GoalType _goalType = GoalType::Maintenance;
	double _targetValue = 0;
	time_t _startDate = std::time(nullptr);
	time_t _deadline = time_t(0);
	bool isAchieved = false;
public:
	FitnessGoal() = default;
	FitnessGoal(GoalType goalType, double targetValue, time_t deadline);
};

