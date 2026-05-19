#include "ExerciseEntry.h"

ExerciseEntry::ExerciseEntry(std::shared_ptr<Exercise> exercise, int durationMinutes)
	: _exercise(std::move(exercise))
	, _durationMinutes(durationMinutes) { }
