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
	std::vector<const Exercise*> _favoriteExercises;
public:
	Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app);

	const std::vector<FoodEntry>& getFoodDiary() const;
	const std::vector<ExerciseEntry>& getExerciseDiary() const;
	const FitnessGoal& getGoal() const;
	const std::vector<const Exercise*>& getFavoriteExercises() const;

	void setGoals(GoalType goalType, double targetValue, time_t deadline);
	void logFood(const std::string& foodName, int quantityGrams);
	void logExercise(const std::string& exerciseName, int durationMinutes);
	void viewDailySummary() const;
	void viewProgress() const;
	void calculateBMI() const;
	void calculateBMR() const;
	std::vector<const Exercise*> generateWorkoutPlan(int durationMinutes) const;
	void addToFavorites(const std::string& exerciseName);
	void viewFavorites() const;
};
