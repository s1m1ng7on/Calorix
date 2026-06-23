#pragma once
#include "User.h"

class Calorix;

class Admin : public User
{
public:
	Admin(std::string username, std::string password, int age, double weight, int height, Gender gender, ActivityLevel activityLevel, Calorix* app);

	bool isAdmin() const override;
	void blockUser(const std::string& username);
	void addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g);

	// Adding an exercise with suggested duration
	void addExercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup);
	void updateFood(const std::string& name, int newCaloriesPer100g);
};

