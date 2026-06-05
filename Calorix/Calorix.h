#pragma once
#include "vector"
#include "memory"
#include "User.h"
#include "string"
#include "Food.h"
#include "Exercise.h"

class Calorix
{
private:
	std::vector<std::unique_ptr<User>> _users;
	std::vector<std::shared_ptr<Food>> _foods;
	std::vector<std::shared_ptr<Exercise>> _exercises;
	User* _loggedUser;
	bool isLogged() const;
public:
	Calorix();

	void registerUser(std::string username, std::string password, int age, double weight, int height, Gender gender);
	void login(const std::string& username, const std::string& password);
	void logout();

	std::shared_ptr<Food> getFoodByName(const std::string& foodName) const;
	std::shared_ptr<Exercise> getExerciseByName(const std::string& exerciseName) const;
	const std::vector<std::shared_ptr<Exercise>>& getExercises() const;
};

