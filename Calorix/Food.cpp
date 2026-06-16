#include "Food.h"

Food::Food(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g)
	: _name(std::move(name))
	, _caloriesPer100g(caloriesPer100g)
	, _proteinPer100g(proteinPer100g)
	, _carbsPer100g(carbsPer100g)
	, _fatPer100g(fatPer100g) { }

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

void Food::setCaloriesPer100g(int newCaloriesPer100g) {
	_caloriesPer100g = newCaloriesPer100g;
}
