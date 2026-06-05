#include "ExerciseEntry.h"

time_t ExerciseEntry::getDate() const {
	return _date;
}

int ExerciseEntry::getBurnedCalories() const {
	return (_durationMinutes / 60) * _exercise->getCaloriesBurnedPerHour();
}

ExerciseEntry::ExerciseEntry(std::shared_ptr<Exercise> exercise, int durationMinutes)
	: _exercise(std::move(exercise))
	, _durationMinutes(durationMinutes) { }
