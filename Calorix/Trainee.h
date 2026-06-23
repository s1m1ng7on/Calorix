#pragma once
#include "User.h"
#include <vector>
#include "FoodEntry.h"
#include "ExerciseEntry.h"
#include <memory>
#include "FitnessGoal.h"
#include <expected>

class Trainee : public User
{
private:
	std::vector<FoodEntry> _foodDiary;
	std::vector<ExerciseEntry> _exerciseDiary;
	FitnessGoal _goals;
	std::vector<const Exercise*> _favoriteExercises;
public:
	Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, ActivityLevel activityLevel, Calorix* app);

	const std::vector<FoodEntry>& getFoodDiary() const;
	const std::vector<ExerciseEntry>& getExerciseDiary() const;
	const FitnessGoal& getGoal() const;
	const std::vector<const Exercise*>& getFavoriteExercises() const;

	void setGoals(GoalType goalType, TargetType targetType, double targetValue, time_t deadline);
	std::expected<void, std::string> logFood(const std::string& foodName, int quantityGrams);
	std::expected<void, std::string> logExercise(const std::string& exerciseName, int durationMinutes);
	void logWeight(double newWeight) const;
	std::string viewDailySummary() const;
	std::string viewProgress();
	double calculateBMI() const;
	double calculateBMR() const;
	std::vector<const Exercise*> generateWorkoutPlan(int durationMinutes) const;
	std::expected<void, std::string> addToFavorites(const std::string& exerciseName);
	std::string viewFavorites() const;
};
