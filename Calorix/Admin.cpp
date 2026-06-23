#include "Admin.h"
#include "Calorix.h"

Admin::Admin(std::string username, std::string password, int age, double weight, int height, Gender gender, ActivityLevel activityLevel, Calorix* app)
	: User(std::move(username), std::move(password), age, weight, height, gender, activityLevel, app) {
}

bool Admin::isAdmin() const {
	return true;
}

void Admin::blockUser(const std::string& username) {
	_app->blockUser(username);
}

void Admin::addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) {
	_app->addFood(std::move(name), caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g);
}

// Adding an exercise with suggested duration
void Admin::addExercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup) {
	_app->addExercise(std::move(name), caloriesBurnedPerHour, suggestedDuration, muscleGroup);
}

void Admin::updateFood(const std::string& name, int newCaloriesPer100g) {
	_app->updateFood(name, newCaloriesPer100g);
}
