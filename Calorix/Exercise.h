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
	MuscleGroup _muscleGroup;
};

