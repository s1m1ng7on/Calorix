#pragma once
#include "string"
#include "memory"
#include "Identifiable.hpp"
#include "UserProfile.h"

class User : public Identifiable<User>
{
private:
	std::string _username;
	std::string _password;
	std::unique_ptr<UserProfile> _profile;
public:
	std::string getUsername() const;
	bool authenticate(const std::string& rawPassword) const;

	User(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app);
	virtual ~User() = default;
	//TODO
protected:
	const Calorix* _app;
};

