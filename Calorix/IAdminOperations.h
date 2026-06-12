#pragma once
#include "Food.h"

class IAdminOperations {
public:
	virtual ~IAdminOperations() = default;
	virtual void blockUser(const std::string& username) = 0;
	virtual void addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) = 0;
};
