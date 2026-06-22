#include "Trainee.h"
#include <iostream>
#include "Helper.h"
#include "Calorix.h"

Trainee::Trainee(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app)
	: User(std::move(username), std::move(password), age, weight, height, gender, app) { }

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

void Trainee::setGoals(GoalType goalType, double targetValue, time_t deadline) {
	_goals = FitnessGoal(goalType, targetValue, deadline);
}

void Trainee::logFood(const std::string& foodName, int quantityGrams) {
	auto result = _app->getFoodByName(foodName);

	if (result) {
		FoodEntry newFoodEntry(result.value(), quantityGrams);
		_foodDiary.push_back(std::move(newFoodEntry));

		std::cout << foodName << " logged in your food diary.";
	}
	else {
		std::cout << foodName << " could not be found in the database.";
	}
}

void Trainee::logExercise(const std::string& exerciseName, int durationMinutes) {
	auto result = _app->getExerciseByName(exerciseName);

	if (result) {
		ExerciseEntry newExerciseEntry(result.value(), durationMinutes);
		_exerciseDiary.push_back(std::move(newExerciseEntry));

		std::cout << exerciseName << " logged in your exercise diary.";
	}
	else {
		std::cout << exerciseName << " could not be found in the database.";
	}
}

void Trainee::viewDailySummary() const {
	int totalConsumedCalories = 0;
	int totalProtein = 0;
	int totalCarbs = 0;
	int totalFat = 0;

	int totalBurnedCalories = 0;

	for (const auto& foodEntry : _foodDiary) {
		if (Helper::isToday(foodEntry.getDate())) {
			totalConsumedCalories += foodEntry.getNutrient(Nutrient::Calories);
			totalProtein += foodEntry.getNutrient(Nutrient::Protein);
			totalCarbs += foodEntry.getNutrient(Nutrient::Carbs);
			totalFat += foodEntry.getNutrient(Nutrient::Fat);
		}
	}

	for (const auto& exerciseEntry : _exerciseDiary) {
		if (Helper::isToday(exerciseEntry.getDate())) {
			totalBurnedCalories += exerciseEntry.getBurnedCalories();
		}
	}

	int netCaloricBalance = totalConsumedCalories - totalBurnedCalories;

	std::cout
		<< "--DAILY SUMMARY--"
		<< std::endl
		<< "Calories consumed: "
		<< totalConsumedCalories
		<< " kcal"
		<< std::endl
		<< "Protein: "
		<< totalProtein
		<< " g"
		<< std::endl
		<< "Carbs: "
		<< totalCarbs
		<< " g"
		<< std::endl
		<< "Fat: "
		<< totalFat
		<< " g"
		<< std::endl
		<< "Burned Calories: "
		<< totalBurnedCalories
		<< " kcal"
		<< std::endl
		<< std::endl
		<< "Net Caloric Balance: "
		<< netCaloricBalance
		<< " kcal"
		<< std::endl;
}

void Trainee::viewProgress() const {
	GoalType currentGoal = _goals.getGoalType();
	
	if (currentGoal == GoalType::Maintenance) {
		std::cout << "You are currently maintaining." << std::endl;
		return;
	}

	double currentWeight = _profile->getWeight();
	double targetWeight = _goals.getTargetValue();

	if (currentGoal == GoalType::Bulking) {
		if (currentWeight >= targetWeight) {
			std::cout << "Congratulations! You have reached (or exceeded) your bulking target weight!" << std::endl;
		}
		else {
			double weightLeft = targetWeight - currentWeight;
			std::cout << "You need to bulk another " << weightLeft << " kg to reach your target." << std::endl;
		}
	}
	else if (currentGoal == GoalType::WeightLoss) {
		if (currentWeight <= targetWeight) {
			std::cout << "Congratulations! You have reached (or dropped below) your cutting target weight!" << std::endl;
		}
		else {
			double weightLeft = currentWeight - targetWeight;
			std::cout << "You need to lose another " << weightLeft << " kg to reach your target." << std::endl;
		}
	}
}

void Trainee::calculateBMI() const {
	double BMI = _profile->getWeight() / pow(_profile->getHeight() / 100.0, 2);

	std::cout
		<< "BMI: "
		<< BMI
		<< std::endl;
}

void Trainee::calculateBMR() const {
	double BMR = 10 * _profile->getWeight()
		+ 6.25 * _profile->getHeight()
		- 5 * _profile->getAge()
		+ (_profile->getGender() == Gender::Male ? 5 : -161);

	std::cout
		<< "BMR: "
		<< BMR
		<< std::endl;
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

void Trainee::addToFavorites(const std::string& exerciseName) {
	auto exercise = _app->getExerciseByName(exerciseName);

	if (exercise) {
		auto it = std::find(_favoriteExercises.begin(), _favoriteExercises.end(), exercise.value());
		if (it == _favoriteExercises.end()) {
			_favoriteExercises.push_back(exercise.value());
			std::cout << "Exercise '" + exerciseName + "' was successfully added to your Favorites." << std::endl;
		}
		else {
			throw std::invalid_argument("Exercise '" + exerciseName + "' is already in your Favorites.");
		}
	}
}

void Trainee::viewFavorites() const {
	for (const auto& exercise : _favoriteExercises) {
		std::cout << *exercise << std::endl;
	}
}

