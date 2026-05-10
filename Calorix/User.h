#pragma once
#include "string"
#include "memory"
#include "UserProfile.h"

class User
{
private:
	static int generateId();

	const int _userId;
	std::string _username;
	std::string _password;
	std::unique_ptr<UserProfile> _profile;
public:
	std::string getUsername() const;
	bool authenticate(const std::string& rawPassword) const;

	User(std::string username, std::string password, int age, double weight, int height, UserProfile::Gender gender);
	//TODO
};

