#include "User.h"

int User::generateId() {
	static int nextId = 1;
	return nextId++;
}

std::string User::getUsername() const {
	return _username;
}

bool User::authenticate(const std::string& rawPassword) const {
	return rawPassword == _password;
}

User::User(std::string username, std::string password, int age, double weight, int height, UserProfile::Gender gender)
	: _userId(generateId())
	, _username(std::move(username))
	, _password(std::move(password))
	, _profile(std::make_unique<UserProfile>(age, weight, height, gender)) { }