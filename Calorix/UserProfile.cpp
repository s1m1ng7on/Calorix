#include "UserProfile.h"

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

UserProfile::UserProfile(int age, double weight, int height, Gender gender)
	: _age(age), _weight(weight), _height(height), _gender(gender) { }
