#include "Food.h"

const std::string& Food::getName() const {
	return _name;
}

int Food::getCaloriesPer100g() const {
	return _caloriesPer100g;
}

int Food::getProteinPer100g() const {
	return _proteinPer100g;
}

int Food::getCarbsPer100g() const {
	return _carbsPer100g;
}

int Food::getFatPer100g() const {
	return _fatPer100g;
}
