#include "Trainee.h"
#include <iostream>
#include "CalorixHelper.h"
#include "Calorix.h"
#include <sstream>

Trainee::Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, ActivityLevel activityLevel, Calorix* app)
	: User(std::move(username), std::move(password), age, weight, height, gender, activityLevel, app) { }

const std::vector<FoodEntry>& Trainee::getFoodDiary() const {
	return _foodDiary;
}

const std::vector<ExerciseEntry>& Trainee::getExerciseDiary() const {
	return _exerciseDiary;
}

const FitnessGoal& Trainee::getGoal() const {
	return _goals;
}

const std::vector<const Exercise*>& Trainee::getFavoriteExercises() const {
	return _favoriteExercises;
}

void Trainee::setGoals(GoalType goalType, TargetType targetType, double targetValue, time_t deadline) {
	_goals = FitnessGoal(goalType, targetType, targetValue, deadline);
}

std::expected<void, std::string> Trainee::logFood(const std::string& foodName, int quantityGrams) {
	auto result = _app->getFoodByName(foodName);

	if (result) {
		FoodEntry newFoodEntry(result.value(), quantityGrams);
		_foodDiary.push_back(std::move(newFoodEntry));
		return { };
	}
	else {
		return std::unexpected(std::format("{} could not be found in foods.", foodName));
	}
}

std::expected<void, std::string> Trainee::logExercise(const std::string& exerciseName, int durationMinutes) {
	auto result = _app->getExerciseByName(exerciseName);

	if (result) {
		ExerciseEntry newExerciseEntry(result.value(), durationMinutes);
		_exerciseDiary.push_back(std::move(newExerciseEntry));
		return { };
	}
	else {
		return std::unexpected(std::format("{} could not be found in exercises.", exerciseName));
	}
}

void Trainee::logWeight(double newWeight) const {
	_profile->setWeight(newWeight);
}

std::string Trainee::viewDailySummary() const {
	int totalConsumedCalories = 0;
	int totalProtein = 0;
	int totalCarbs = 0;
	int totalFat = 0;
	int totalBurnedCalories = 0;

	for (const auto& foodEntry : _foodDiary) {
		if (CalorixHelper::isToday(foodEntry.getDate())) {
			totalConsumedCalories += foodEntry.getNutrient(Nutrient::Calories);
			totalProtein += foodEntry.getNutrient(Nutrient::Protein);
			totalCarbs += foodEntry.getNutrient(Nutrient::Carbs);
			totalFat += foodEntry.getNutrient(Nutrient::Fat);
		}
	}

	for (const auto& exerciseEntry : _exerciseDiary) {
		if (CalorixHelper::isToday(exerciseEntry.getDate())) {
			totalBurnedCalories += exerciseEntry.getBurnedCalories();
		}
	}

	int netCaloricBalance = totalConsumedCalories - totalBurnedCalories;

	return std::format(
		"--DAILY SUMMARY--\n"
		"Calories consumed: {} kcal\n"
		"Protein: {} g\n"
		"Carbs: {} g\n"
		"Fat: {} g\n"
		"Burned Calories: {} kcal\n\n"
		"Net Caloric Balance: {} kcal\n",
		totalConsumedCalories, totalProtein, totalCarbs, totalFat, totalBurnedCalories, netCaloricBalance
	);
}

std::string Trainee::viewProgress() {
	GoalType currentGoal = _goals.getGoalType();
	TargetType targetType = _goals.getTargetType();
	double targetValue = _goals.getTargetValue();

	if (currentGoal == GoalType::Maintenance) {
		_goals.setIsAchieved(true);
		return "You are currently maintaining.";
	}

	if (targetType == TargetType::Calories) {
		int totalConsumedCalories = 0;
		int totalBurnedCalories = 0;

		for (const auto& foodEntry : _foodDiary) {
			if (CalorixHelper::isToday(foodEntry.getDate())) {
				totalConsumedCalories += foodEntry.getNutrient(Nutrient::Calories);
			}
		}
		for (const auto& exerciseEntry : _exerciseDiary) {
			if (CalorixHelper::isToday(exerciseEntry.getDate())) {
				totalBurnedCalories += exerciseEntry.getBurnedCalories();
			}
		}

		int netCaloricBalance = totalConsumedCalories - totalBurnedCalories;
		double bmr = calculateBMR();

		if (currentGoal == GoalType::WeightLoss) {
			double targetCalories = bmr - std::abs(targetValue);
			if (netCaloricBalance <= targetCalories) {
				_goals.setIsAchieved(true);
				return "Congratulations! You are successfully within your calorie deficit today!";
			}
			else {
				_goals.setIsAchieved(false);
				return std::format("You need to burn {} kcal more today to reach your deficit limit.", (netCaloricBalance - targetCalories));
			}
		}
		else if (currentGoal == GoalType::Bulking) {
			double targetCalories = bmr + std::abs(targetValue);
			if (netCaloricBalance >= targetCalories) {
				_goals.setIsAchieved(true);
				return "Congratulations! You hit your calorie surplus today!";
			}
			else {
				_goals.setIsAchieved(false);
				return std::format("You need to consume {} kcal more today to reach your surplus target.", (targetCalories - netCaloricBalance));
			}
		}
	}

	double currentWeight = _profile->getWeight();

	if (currentGoal == GoalType::Bulking) {
		if (currentWeight >= targetValue) {
			_goals.setIsAchieved(true);
			return "Congratulations! You have reached your bulking target weight!";
		}
		else {
			_goals.setIsAchieved(false);
			return std::format("You need to bulk another {} kg to reach your target.", (targetValue - currentWeight));
		}
	}
	else if (currentGoal == GoalType::WeightLoss) {
		if (currentWeight <= targetValue) {
			_goals.setIsAchieved(true);
			return "Congratulations! You have reached your cutting target weight!";
		}
		else {
			_goals.setIsAchieved(false);
			return std::format("You need to lose another {} kg to reach your target.", (currentWeight - targetValue));
		}
	}

	return "";
}

double Trainee::calculateBMI() const {
	return _profile->getWeight() / pow(_profile->getHeight() / 100.0, 2);
}

double Trainee::calculateBMR() const {
	return
		10 * _profile->getWeight()
		+ 6.25 * _profile->getHeight()
		- 5 * _profile->getAge()
		+ (_profile->getGender() == Gender::Male ? 5 : -161);
}

std::vector<const Exercise*> Trainee::generateWorkoutPlan(int durationMinutes) const {
	const auto& exercises = _app->getExercises();

	int rows = exercises.size() + 1;
	int columns = durationMinutes + 1;

	int** knapsackMatrix = new int*[rows];
	for (int i = 0; i < rows; i++) {
		knapsackMatrix[i] = new int[columns];
	}

	for (int j = 0; j < columns; j++) {
		knapsackMatrix[0][j] = 0;
	}

	for (int i = 1; i < rows; i++) {
		int currentDuration = exercises[i - 1]->getSuggestedDuration();
		int currentCalories = exercises[i - 1]->getCaloriesForSuggestedDuration();

		for (int j = 0; j < columns; j++) {
			int optionA = knapsackMatrix[i - 1][j];

			if (j >= exercises[i - 1]->getSuggestedDuration()) {
				int optionB = currentCalories + knapsackMatrix[i - 1][j - currentDuration];
				knapsackMatrix[i][j] = std::max(optionA, optionB);
			}
			else {
				knapsackMatrix[i][j] = optionA;
			}
		}
	}

	std::vector<const Exercise*> workoutPlan;
	int currentColumn = durationMinutes;
	for (int i = rows - 1; i > 0; i--) {
		if (knapsackMatrix[i][currentColumn] != knapsackMatrix[i - 1][currentColumn]) {
			workoutPlan.push_back(exercises[i - 1].get());
			currentColumn -= exercises[i - 1]->getSuggestedDuration();
		}
	}

	for (int i = 0; i < rows; i++) {
		delete[] knapsackMatrix[i];
	}
	delete[] knapsackMatrix;

	return workoutPlan;
}

std::expected<void, std::string> Trainee::addToFavorites(const std::string& exerciseName) {
	auto exercise = _app->getExerciseByName(exerciseName);

	if (!exercise) {
		return std::unexpected(std::format("Exercise '{}' could not be found.", exerciseName));
	}

	auto it = std::find(_favoriteExercises.begin(), _favoriteExercises.end(), exercise.value());
	if (it == _favoriteExercises.end()) {
		_favoriteExercises.push_back(exercise.value());
		return { };
	}
	else {
		return std::unexpected(std::format("Exercise '{}' is already in your Favorites.", exerciseName));
	}
}

std::string Trainee::viewFavorites() const {
	if (_favoriteExercises.empty())
		return "There are no favorite exercises added yer.";

	std::stringstream ss;
	for (const auto& exercise : _favoriteExercises) {
		ss << *exercise << std::endl;
	}

	return ss.str();
}

