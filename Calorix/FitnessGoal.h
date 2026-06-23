#pragma once
#include <ctime>

enum class GoalType {
	WeightLoss,
	Bulking,
	Maintenance
};

enum class TargetType {
	Weight,
	Calories
};

class FitnessGoal
{
private:
	GoalType _goalType = GoalType::Maintenance;
	TargetType _targetType = TargetType::Weight;
	double _targetValue = 0;
	time_t _startDate = std::time(nullptr);
	time_t _deadline = time_t(0);
	bool _isAchieved = false;
public:
	FitnessGoal() = default;
	FitnessGoal(GoalType goalType, TargetType targetType, double targetValue, time_t deadline);
	FitnessGoal(GoalType goalType, TargetType targetType, double targetValue, time_t startDate, time_t deadline, bool isAchieved);

	GoalType getGoalType() const;
	TargetType getTargetType() const;
	double getTargetValue() const;
	time_t getStartDate() const;
	time_t getDeadline() const;
	bool getIsAchieved() const;

	void setIsAchieved(bool isAchieved);
};

