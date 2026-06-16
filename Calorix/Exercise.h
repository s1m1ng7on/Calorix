#pragma once
#include "Identifiable.hpp"
#include <string>

enum class MuscleGroup {
	Chest,
	Back,
	Shoulders,
	Biceps,
	Triceps,
	Quads,
	Hamstrings,
	Core
};

class Exercise : Identifiable<Exercise>
{
private:
	std::string _name;
	int _caloriesBurnedPerHour;

	// Used for the knapsack algorithm
	int _suggestedDuration;

	MuscleGroup _muscleGroup;
public:
	Exercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, MuscleGroup muscleGroup);

	const std::string& getName() const;
	int getCaloriesBurnedPerHour() const;
	int getSuggestedDuration() const;
	int getCaloriesForSuggestedDuration() const;

	friend std::ostream& operator<<(std::ostream& os, const Exercise& exercise);
};

