#include <iostream>
#include <string>
#include "Calorix.h"

bool Calorix::isLogged() const {
    return _loggedUser != nullptr;
}

Calorix::Calorix()
    : _loggedUser(nullptr) { }

void Calorix::registerUser(std::string username, std::string password, int age, double weight, int height, UserProfile::Gender gender) {
    if (isLogged()) {
        std::cout << "This action requires you to log out." << std::endl;
        return;
    }

    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& currentUser) {
        return currentUser->getUsername() == username;
        });

    if (it != _users.end()) {
        std::cout << "User with username " << username << " already exists." << std::endl;
        return;
    }

    std::unique_ptr<User> newUser = std::make_unique<User>(username, password, age, weight, height, gender);
    _loggedUser = newUser.get();
    _users.push_back(std::move(newUser));

    std::cout << "Register successful! Welcome to Calorix, " << username << "!" << std::endl;
}

void Calorix::login(const std::string& username, const std::string& password) {
    if (isLogged()) {
        std::cout << "This action requires you to log out." << std::endl;
        return;
    }

    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& currentUser) {
        return currentUser->getUsername() == username;
    });

    if (it == _users.end()) {
        std::cout << "An user with this username doesn't exist." << std::endl;
        return;
    }

    auto foundUser = it->get();

    if (foundUser->authenticate(password)) {
        _loggedUser = foundUser;
        std::cout << "Login successful! Welcome to Calorix, " << username << "!" << std::endl;
    }
    else {
        std::cout << "Wrong password!" << std::endl;
    }
}

void Calorix::logout() {
    if (isLogged()) {
        _loggedUser = nullptr;
        std::cout << "Logout successful." << std::endl;
    }
    else {
        std::cout << "You are not logged in currently." << std::endl;
    }
}
