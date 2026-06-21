#include <iostream>
#include <string>
#include "Calorix.h"
#include <expected>
#include "CalorixTextFileDataManager.h"

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

User* Calorix::addUserInternal(std::string username, std::string password, int age, double weight, int height, Gender gender) {
    auto it = std::find_if(_users.begin(), _users.end(), [&](const auto& currentUser) {
        return currentUser->getUsername() == username;
        });

    if (it != _users.end())
        throw std::runtime_error("User with username " + username + " already exists.");

    std::unique_ptr<User> newUser = std::make_unique<User>(std::move(username), std::move(password), age, weight, height, gender, this);
    User* rawUser = newUser.get();
    _users.push_back(std::move(newUser));

    return rawUser;
}

void Calorix::addFoodInternal(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) {
    if (getFoodByName(name))
        throw std::runtime_error("Food item with the same name already exists.");

    _foods.push_back(std::make_shared<Food>(std::move(name), caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g));
}

void Calorix::addExerciseInternal(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup) {
    if (getExerciseByName(name))
        throw std::runtime_error("Exercise with the same name already exists.");

    _exercises.push_back(std::make_shared<Exercise>(std::move(name), caloriesBurnedPerHour, suggestedDuration, muscleGroup));
}

Calorix::Calorix()
    : _loggedUser(nullptr)
    , _ui(*this) { }

Calorix::Calorix(std::string filename)
    : _loggedUser(nullptr)
    , _filename(std::move(filename))
    , _ui(*this) {
    CalorixTextFileDataManager::loadFromFile(_filename, *this);
}

Calorix::~Calorix() {
    CalorixTextFileDataManager::saveToFile(_filename, *this);
}

Calorix& Calorix::getInstance() {
    static Calorix instance("calorix-input.txt");
    return instance;
}

void Calorix::run() {
    _ui.run();
}

bool Calorix::isLogged() const {
    return _loggedUser != nullptr;
}

User* Calorix::getLoggedUser() const {
    return _loggedUser;
}

void Calorix::registerUser(std::string username, std::string password, int age, double weight, int height, Gender gender) {
    ensureLoggedOut();

    User* newUser = addUserInternal(std::move(username), std::move(password), age, weight, height, gender);

    if (newUser != nullptr)
        _loggedUser = newUser;
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

void Calorix::addFood(std::string name, int caloriesPer100g, int proteinPer100g, int carbsPer100g, int fatPer100g) {
    ensureLoggedIn();
    ensureIsAdmin();

    addFoodInternal(std::move(name), caloriesPer100g, proteinPer100g, carbsPer100g, fatPer100g);
}

void Calorix::addExercise(std::string name, int caloriesBurnedPerHour, int suggestedDuration, std::string muscleGroup) {
    ensureLoggedIn();
    ensureIsAdmin();

    addExerciseInternal(std::move(name), caloriesBurnedPerHour, suggestedDuration, std::move(muscleGroup));
}

void Calorix::updateFood(const std::string& name, int newCaloriesPer100g) {
    auto result = getFoodByName(name);

    if (result)
        result.value()->setCaloriesPer100g(newCaloriesPer100g);
    else
        throw std::runtime_error("Update failed: " + result.error());
}

std::expected<Food*, std::string> Calorix::getFoodByName(const std::string& foodName) const {
    for (const auto& food : _foods) {
        if (food->getName() == foodName)
            return food.get();
    }

    return std::unexpected("Food with name '" + foodName + "' was not found.");
}

std::expected<const Exercise*, std::string> Calorix::getExerciseByName(const std::string& exerciseName) const {
    for (const auto& exercise : _exercises) {
        if (exercise->getName() == exerciseName)
            return exercise.get();
    }

    return std::unexpected("Exercise with name '" + exerciseName + "' was not found.");
}

const std::vector<std::shared_ptr<Exercise>>& Calorix::getExercises() const {
    return _exercises;
}
