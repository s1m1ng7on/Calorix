#pragma once
#include "string"
#include "memory"
#include "Identifiable.hpp"
#include "UserProfile.h"
#include "Calorix.h"

class User : public Identifiable<User>
{
private:
	friend class CalorixTextFileDataManager;

	std::string _username;
	std::string _password;
public:
	const std::string& getUsername() const;
	bool authenticate(const std::string& rawPassword) const;
	virtual bool isAdmin() const;

	User(std::string username, std::string password, int age, double weight, int height, Gender gender, Calorix* app);
	virtual ~User() = default;
protected:
	std::unique_ptr<UserProfile> _profile;
	Calorix* _app;
};

