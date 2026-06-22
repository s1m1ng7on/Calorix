#include "ExerciseEntry.h"

ExerciseEntry::ExerciseEntry(const Exercise* exercise, int durationMinutes)
	: _exercise(exercise)
	, _durationMinutes(durationMinutes) {
}

const std::string& ExerciseEntry::getExerciseName() const {
	return _exercise->getName();
}

int ExerciseEntry::getDurationMinutes() const {
	return _durationMinutes;
}

time_t ExerciseEntry::getDate() const {
	return _date;
}

int ExerciseEntry::getBurnedCalories() const {
	return (_durationMinutes / 60.00) * _exercise->getCaloriesBurnedPerHour();
}
