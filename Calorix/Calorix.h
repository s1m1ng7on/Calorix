#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include <string>
#include "Food.h"
#include "Exercise.h"
#include "ITraineeOperations.h"
#include "IAdminOperations.h"
#include <expected>

class Calorix : public ITraineeOperations, public IAdminOperations
{
	friend class CalorixTextFileDataManager;
private:
	std::vector<std::unique_ptr<User>> _users;
	const std::string _filename;

	//Food items and exercises are shared_ptr on purpose
	//Multiple Calorix instances may contain the same food items or exercises
	std::vector<std::shared_ptr<Food>> _foods;
	std::vector<std::shared_ptr<Exercise>> _exercises;

	User* _loggedUser;

	bool isLogged() const;
	void ensureLoggedIn() const;
	void ensureLoggedOut() const;
	void ensureIsAdmin() const;

	User* addUserInternal(std::string username, std::string password, int age, double weight, int height, Gender gender);
	void addFoodInternal(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g);
	void addExerciseInternal(std::string name, int caloriesBurnedPerHour, int suggestedDuration, MuscleGroup muscleGroup);
public:
	Calorix();
	Calorix(std::string filename);
	~Calorix();

	void registerUser(std::string username, std::string password, int age, double weight, int height, Gender gender);
	void login(const std::string& username, const std::string& password);
	void logout();

	void blockUser(const std::string& username) override;
	void addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) override;
	void addExercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, MuscleGroup muscleGroup) override;
	void updateFood(const std::string& name, int newCaloriesPer100g) override;

	std::expected<const Food*, std::string> getFoodByName(const std::string& foodName) const override;
	std::expected<const Exercise*, std::string> getExerciseByName(const std::string& exerciseName) const override;
	const std::vector<std::shared_ptr<Exercise>>& getExercises() const override;
};

