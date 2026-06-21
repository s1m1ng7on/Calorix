#pragma once
#include "User.h"
#include <stdexcept>
#include "Calorix.h"

class Admin : public User
{
public:
	Admin(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app)
		: User(std::move(username), std::move(password), age, weight, height, gender, app) { }

	bool isAdmin() const override {
		return true;
	}

	void blockUser(const std::string& username) {
		_app->blockUser(username);
	}

	void addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) {
		_app->addFood(std::move(name), caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g);
	}

	// Adding an exercise with suggested duration
	void addExercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, MuscleGroup muscleGroup) {
		_app->addExercise(std::move(name), caloriesBurnedPerHour, suggestedDuration, muscleGroup);
	}

	void updateFood(const std::string& name, int newCaloriesPer100g) {
		_app->updateFood(name, newCaloriesPer100g);
	}
};

