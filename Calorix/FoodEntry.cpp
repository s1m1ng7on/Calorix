#include "FoodEntry.h"

time_t FoodEntry::getDate() const {
	return _date;
}

FoodEntry::FoodEntry(const Food* food, int quantityGrams)
	: _food(food)
	, _quantityGrams(quantityGrams) { }

int FoodEntry::getNutrient(Nutrient type) const {
	double value = 0;

	switch (type) {
		case Nutrient::Calories: value = _food->getCaloriesPer100g(); break;
		case Nutrient::Protein: value = _food->getProteinPer100g(); break;
		case Nutrient::Carbs: value = _food->getCarbsPer100g(); break;
		case Nutrient::Fat: value = _food->getFatPer100g(); break;
	}

	return (static_cast<double>(_quantityGrams) / 100.0) * value;
}
