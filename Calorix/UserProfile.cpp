#include "UserProfile.h"

UserProfile::UserProfile(int age, double weight, int height, Gender gender, ActivityLevel activityLevel)
	: _age(age)
	, _weight(weight)
	, _height(height)
	, _gender(gender)
	, _activityLevel(activityLevel) { }

int UserProfile::getAge() const {
	return _age;
}

double UserProfile::getWeight() const {
	return _weight;
}

int UserProfile::getHeight() const {
	return _height;
}

Gender UserProfile::getGender() const {
	return _gender;
}

ActivityLevel UserProfile::getActivityLevel() const {
	return _activityLevel;
}

void UserProfile::setWeight(double newWeight) {
	_weight = newWeight;
}
