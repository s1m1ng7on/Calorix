#pragma once
#include <memory>
#include "Food.h"
#include "Exercise.h"
#include <vector>
#include <expected>

class ITraineeOperations {
public:
	virtual ~ITraineeOperations() = default;

	virtual std::expected<const Food*, std::string> getFoodByName(const std::string& foodName) const = 0;
	virtual std::expected<const Exercise*, std::string> getExerciseByName(const std::string& exerciseName) const = 0;
	virtual const std::vector<std::shared_ptr<Exercise>>& getExercises() const = 0;
};
