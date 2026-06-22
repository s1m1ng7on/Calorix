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
	bool _isAchieved = false;
public:
	FitnessGoal() = default;
	FitnessGoal(GoalType goalType, double targetValue, time_t deadline);
	FitnessGoal(GoalType goalType, double targetValue, time_t startDate, time_t deadline, bool isAchieved);

	GoalType getGoalType() const;
	double getTargetValue() const;
	time_t getStartDate() const;
	time_t getDeadline() const;
	bool getIsAchieved() const;
};

