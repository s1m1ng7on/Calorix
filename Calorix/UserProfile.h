#pragma once
class UserProfile
{
public:
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
private:
	int _age;
	double _weight;
	int _height;
	Gender _gender;
	ActivityLevel _activityLevel;
public:
	UserProfile(int age, double weight, int height, Gender gender);
};

