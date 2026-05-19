#pragma once
#include <string>
#include "Identifiable.hpp"

class Food : Identifiable<Food>
{
private:
	std::string _name;
	int _caloriesPer100g;
	int _proteinPer100g;
	int _carbsPer100g;
	int _fatPer100g;
public:
	const std::string& getName() const;
};

