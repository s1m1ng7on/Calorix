#pragma once
#include "string"
#include "memory"
#include "Identifiable.hpp"
#include "UserProfile.h"
#include "Calorix.h"

class User : public Identifiable<User>
{
private:
	std::string _username;
	std::string _password;
public:
	std::string getUsername() const;
	bool authenticate(const std::string& rawPassword) const;

	User(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app);
	virtual ~User() = default;
	//TODO
protected:
	std::unique_ptr<UserProfile> _profile;
	const Calorix* _app;
};

