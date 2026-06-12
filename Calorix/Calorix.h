#pragma once
#include "vector"
#include "memory"
#include "User.h"
#include "string"
#include "Food.h"
#include "Exercise.h"
#include <iostream>
#include <algorithm>
#include "ITraineeOperations.h"
#include "IAdminOperations.h"

class Calorix : public ITraineeOperations, public IAdminOperations
{
private:
	std::vector<std::unique_ptr<User>> _users;
	std::vector<std::shared_ptr<Food>> _foods;
	std::vector<std::shared_ptr<Exercise>> _exercises;
	User* _loggedUser;
	bool isLogged() const;
	void ensureLoggedIn() const;
	void ensureLoggedOut() const;
	void ensureIsAdmin() const;
public:
	Calorix();

	void registerUser(std::string username, std::string password, int age, double weight, int height, Gender gender);
	void login(const std::string& username, const std::string& password);
	void logout();
	void blockUser(const std::string& username) override;

	void addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) override {
		/*shared_ptr(std::move(name), caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g);
		_foods.push_back(food);*/
	}

	std::shared_ptr<Food> getFoodByName(const std::string& foodName) const override;
	std::shared_ptr<Exercise> getExerciseByName(const std::string& exerciseName) const override;
	const std::vector<std::shared_ptr<Exercise>>& getExercises() const override;
};

