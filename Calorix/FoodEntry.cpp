#include "FoodEntry.h"

time_t FoodEntry::getDate() const {
	return _date;
}

FoodEntry::FoodEntry(std::shared_ptr<Food> food, int quantityGrams)
	: _food(std::move(food))
	, _quantityGrams(quantityGrams) { }
