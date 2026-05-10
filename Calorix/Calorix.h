#pragma once
#include "vector"
#include "memory"
#include "User.h"
#include "string"

class Calorix
{
private:
	std::vector<std::unique_ptr<User>> _users;
	User* _loggedUser;
	bool isLogged() const;
public:
	Calorix();

	void registerUser(std::string username, std::string password, int age, double weight, int height, UserProfile::Gender gender);
	void login(const std::string& username, const std::string& password);
	void logout();
};

