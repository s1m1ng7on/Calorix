#include "Exercise.h"
#include <iostream>

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

std::ostream& operator<<(std::ostream& os, const Exercise& exercise) {
	os << "Name: " << exercise._name
		<< ", Duration: " << exercise._suggestedDuration << " mins"
		<< ", Calories: " << exercise.getCaloriesForSuggestedDuration() << " kcal";
	return os;
}
