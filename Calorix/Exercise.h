#pragma once
#include "Identifiable.hpp"
#include <string>

class Exercise : Identifiable<Exercise>
{
private:
	std::string _name;
	int _caloriesBurnedPerHour;

	// Used for the knapsack algorithm
	int _suggestedDuration;

	std::string _muscleGroup;
public:
	Exercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup);

	const std::string& getName() const;
	int getCaloriesBurnedPerHour() const;
	int getSuggestedDuration() const;
	int getCaloriesForSuggestedDuration() const;
	const std::string& getMuscleGroup() const;

	friend std::ostream& operator<<(std::ostream& os, const Exercise& exercise);
};

