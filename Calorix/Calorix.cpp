#include <iostream>
#include <string>
#include "Calorix.h"

bool Calorix::isLogged() const {
    return _loggedUser != nullptr;
}

void Calorix::ensureLoggedIn() const {
    if (!isLogged())
        throw std::logic_error("This action requires you to log in.");
}

void Calorix::ensureLoggedOut() const {
    if (isLogged())
        throw std::logic_error("This action requires you to log out.");
}

void Calorix::ensureIsAdmin() const {
    if (!_loggedUser->isAdmin())
        throw std::logic_error("This action required you to be an admin.");
}

Calorix::Calorix()
    : _loggedUser(nullptr) { }

void Calorix::registerUser(std::string username, std::string password, int age, double weight, int height, Gender gender) {
    ensureLoggedOut();

    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& currentUser) {
        return currentUser->getUsername() == username;
    });

    if (it != _users.end())
        throw std::runtime_error("User with username " + username + " already exists.");

    std::unique_ptr<User> newUser = std::make_unique<User>(username, password, age, weight, height, gender, this);
    _loggedUser = newUser.get();
    _users.push_back(std::move(newUser));
}

void Calorix::login(const std::string& username, const std::string& password) {
    ensureLoggedOut();

    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& currentUser) {
        return currentUser->getUsername() == username;
    });

    if (it == _users.end())
        throw std::runtime_error("An user with this username does not exist.");

    auto foundUser = it->get();

    if (foundUser->authenticate(password))
        _loggedUser = foundUser;
    else
        throw std::runtime_error("Wrong password!");
}

void Calorix::logout() {
    ensureLoggedIn();
    _loggedUser = nullptr;
}

void Calorix::blockUser(const std::string& username) {
    ensureLoggedIn();
    ensureIsAdmin();

    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& user) {
        return user->getUsername() == username;
        });

    if (it == _users.end())
        throw std::runtime_error("User with this username does not exist.");

    _users.erase(it);
}

std::shared_ptr<Food> Calorix::getFoodByName(const std::string& foodName) const {
    auto it = std::find_if(_foods.begin(), _foods.end(), [&](const auto& currentFood) {
        return currentFood->getName() == foodName;
    });

    if (it == _foods.end()) {
        throw std::runtime_error("Food item does not exist.");
    }

    return *it;
}

std::shared_ptr<Exercise> Calorix::getExerciseByName(const std::string& exerciseName) const {
    for (const auto& exercise : _exercises) {
        if (exercise->getName() == exerciseName)
            return exercise;
    }

    throw std::invalid_argument("Exercise with name '" + exerciseName + "' was not found.");
}

const std::vector<std::shared_ptr<Exercise>>& Calorix::getExercises() const {
    return _exercises;
}
