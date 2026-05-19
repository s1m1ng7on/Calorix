#include "User.h"

std::string User::getUsername() const {
	return _username;
}

bool User::authenticate(const std::string& rawPassword) const {
	return rawPassword == _password;
}

User::User(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app)
	: _username(std::move(username))
	, _password(std::move(password))
	, _profile(std::make_unique<UserProfile>(age, weight, height, gender))
	, _app(app) { }