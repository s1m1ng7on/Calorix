#pragma once
#include "Identifiable.hpp"
#include <memory>
#include "Food.h"
#include <ctime>

enum class Nutrient {
	Calories,
	Protein,
	Carbs,
	Fat
};

class FoodEntry : Identifiable<FoodEntry>
{
private:
	const Food* _food;
	int _quantityGrams;
	time_t _date = std::time(nullptr);
public:
	FoodEntry(const Food* food, int quantityGrams);

	const std::string& getFoodName() const;
	int getQuantityGrams() const;
	time_t getDate() const;
	int getNutrient(Nutrient type) const;
};

