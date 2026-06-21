#include "ExerciseEntry.h"

time_t ExerciseEntry::getDate() const {
	return _date;
}

int ExerciseEntry::getBurnedCalories() const {
	return (_durationMinutes / 60.00) * _exercise->getCaloriesBurnedPerHour();
}

ExerciseEntry::ExerciseEntry(const Exercise* exercise, int durationMinutes)
	: _exercise(exercise)
	, _durationMinutes(durationMinutes) { }
