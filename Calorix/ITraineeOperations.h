#pragma once
#include <memory>
#include "Food.h"
#include "Exercise.h"
#include <vector>

class ITraineeOperations {
public:
	virtual ~ITraineeOperations() = default;
	virtual std::shared_ptr<Food> getFoodByName(const std::string& foodName) const = 0;
	virtual std::shared_ptr<Exercise> getExerciseByName(const std::string& exerciseName) const = 0;
	virtual const std::vector<std::shared_ptr<Exercise>>& getExercises() const = 0;
};
