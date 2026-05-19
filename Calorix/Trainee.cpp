#include "Trainee.h"
#include <iostream>

Trainee::Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app)
	: User(std::move(username), std::move(password), age, weight, height, gender, app) { }

void Trainee::setGoals(GoalType goalType, double targetValue, time_t deadline) {
	_goals = FitnessGoal(goalType, targetValue, deadline);
}

void Trainee::logFood(const std::string& foodName, int quantityGrams) {
	if (!_app)
		return;

	auto food = _app->getFoodByName(foodName);

	if (food != nullptr) {
		FoodEntry newFoodEntry(food, quantityGrams);
		_foodDiary.push_back(std::move(newFoodEntry));

		std::cout << foodName << " logged in your food diary.";
	}
	else {
		std::cout << foodName << " could not be found in the database.";
	}
}

void Trainee::logExercise(const std::string& exerciseName, int durationMinutes) {
	if (!_app)
		return;

	auto exercise = _app->getExerciseByName(exerciseName);

	if (exercise != nullptr) {
		ExerciseEntry newExerciseEntry(exercise, durationMinutes);
		_exerciseDiary.push_back(std::move(newExerciseEntry));

		std::cout << exerciseName << " logged in your exercise diary.";
	}
	else {
		std::cout << exerciseName << " could not be found in the database.";
	}
}

//void Trainee::viewDailySummary() const {
//	for (const auto& foodEntry : _foodDiary) {
//		if (foodEntry.getDate() == )
//	}
//}

//void showProgress() const;
//double calculateBMI() const;
//double calculateBMR() const;
//std::vector<std::shared_ptr<Exercise>> generateWorkoutPlan(int durationMinutes) const;
//void addToFavorites(const std::string& exerciseName);
//void viewFavorites() const;

