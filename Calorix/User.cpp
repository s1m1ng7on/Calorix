#include "User.h"
#include <stdexcept>
#include "Calorix.h"

const std::string& User::getUsername() const {
	return _username;
}

bool User::authenticate(const std::string& rawPassword) const {
	return rawPassword == _password;
}

User::User(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app)
	: _username(std::move(username))
	, _password(std::move(password))
	, _profile(std::make_unique<UserProfile>(age, weight, height, gender))
	, _app(app) {
	if (_app == nullptr)
		throw std::invalid_argument("Cannot create a User without a valid Calorix app reference.");
}

bool User::isAdmin() const {
	return false;
}