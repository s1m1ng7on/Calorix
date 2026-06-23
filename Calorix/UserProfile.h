#pragma once

enum class Gender {
	Male,
	Female
};

enum class ActivityLevel {
	Sedentary,
	Light,
	Moderate,
	Active,
	VeryActive
};

class UserProfile
{
private:
	int _age;
	double _weight;
	int _height;
	Gender _gender;
	ActivityLevel _activityLevel;
public:
	UserProfile(int age, double weight, int height, Gender gender, ActivityLevel activityLevel);

	int getAge() const;
	double getWeight() const;
	int getHeight() const;
	Gender getGender() const;
	ActivityLevel getActivityLevel() const;

	void setWeight(double newWeight);
};

