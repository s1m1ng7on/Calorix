#pragma once
#include "Identifiable.hpp"
#include <memory>
#include "Exercise.h"
#include <ctime>

class ExerciseEntry : Identifiable<ExerciseEntry>
{
private:
	const Exercise* _exercise;
	int _durationMinutes;
	time_t _date = std::time(nullptr);
public:
	time_t getDate() const;
	int getBurnedCalories() const;
	ExerciseEntry(const Exercise* exercise, int durationMinutes);
};

