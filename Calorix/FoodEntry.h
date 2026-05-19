#pragma once
#include "Identifiable.hpp"
#include <memory>
#include "Food.h"
#include <ctime>

class FoodEntry : Identifiable<FoodEntry>
{
private:
	std::shared_ptr<Food> _food;
	int _quantityGrams;
	time_t _date = std::time(nullptr);
public:
	time_t getDate() const;

	FoodEntry(std::shared_ptr<Food> food, int quantityGrams);
};

