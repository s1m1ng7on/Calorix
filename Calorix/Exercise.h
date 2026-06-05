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
	int _suggestedDuration;			//Used for the knapsack algorithm
	MuscleGroup _muscleGroup;
public:
	const std::string& getName() const;
	int getCaloriesBurnedPerHour() const;
	int getSuggestedDuration() const;
	int getCaloriesForSuggestedDuration() const;

	friend std::ostream& operator<<(std::ostream& os, const Exercise& exercise);
};

