#pragma once
#include "Identifiable.hpp"
#include <memory>
#include "Exercise.h"
#include <ctime>

class ExerciseEntry : Identifiable<ExerciseEntry>
{
private:
	std::shared_ptr<Exercise> _exercise;
	int _durationMinutes;
	time_t _date = std::time(nullptr);
public:
	ExerciseEntry(std::shared_ptr<Exercise> exercise, int durationMinutes);
};

