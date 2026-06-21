#include "Exercise.h"
#include <iostream>

Exercise::Exercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup)
	: _name(std::move(name))
	, _caloriesBurnedPerHour(caloriesBurnedPerHour)
	, _suggestedDuration(suggestedDuration)
	, _muscleGroup(std::move(muscleGroup)) {
}

const std::string& Exercise::getName() const {
	return _name;
}

int Exercise::getCaloriesBurnedPerHour() const {
	return _caloriesBurnedPerHour;
}

int Exercise::getSuggestedDuration() const {
	return _suggestedDuration;
}

int Exercise::getCaloriesForSuggestedDuration() const {
	return (_suggestedDuration / 60.0) * _caloriesBurnedPerHour;
}

const std::string& Exercise::getMuscleGroup() const {
	return _muscleGroup;
}

std::ostream& operator<<(std::ostream& os, const Exercise& exercise) {
	os << "Name: " << exercise._name
		<< ", Duration: " << exercise._suggestedDuration << " mins"
		<< ", Calories: " << exercise.getCaloriesForSuggestedDuration() << " kcal";
	return os;
}
