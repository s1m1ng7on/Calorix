#pragma once
#include "User.h"
#include <vector>
#include "FoodEntry.h"
#include "ExerciseEntry.h"
#include <memory>
#include "FitnessGoal.h"

class Trainee : public User
{
private:
	std::vector<FoodEntry> _foodDiary;
	std::vector<ExerciseEntry> _exerciseDiary;
	FitnessGoal _goals;
	std::vector<std::shared_ptr<Exercise>> _favoriteExercises;
public:
	Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app);

	void setGoals(GoalType goalType, double targetValue, time_t deadline);
	void logFood(const std::string& foodName, int quantityGrams);
	void logExercise(const std::string& exerciseName, int durationMinutes);
	void viewDailySummary() const;
	void viewProgress() const;
	double calculateBMI() const;
	double calculateBMR() const;
	std::vector<std::shared_ptr<Exercise>> generateWorkoutPlan(int durationMinutes) const;
	void addToFavorites(const std::string& exerciseName);
	void viewFavorites() const;
};
