#include "CalorixUIManager.h"
#include "Admin.h"
#include <iostream>
#include "Calorix.h"
#include <expected>
#include "CalorixHelper.h"

CalorixUIManager::CalorixUIManager(Calorix& calorix)
    : _calorix(calorix) {
}

void CalorixUIManager::run() {
    std::cout
        << "Welcome to Calorix!" << "\n"
        << "Type 'help' for available commands." << "\n"
        << "Type 'end' to save & exit." << "\n";

    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "end")
            break;

        try {
            executeCommand(command, ss);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

Trainee* CalorixUIManager::getLoggedTrainee() const {
    return dynamic_cast<Trainee*>(_calorix.getLoggedUser());
}

Admin* CalorixUIManager::getLoggedAdmin() const {
    return dynamic_cast<Admin*>(_calorix.getLoggedUser());
}

void CalorixUIManager::executeCommand(const std::string& command, std::stringstream& ss) {
    if (command == "register")
        handleRegister(ss);
    else if (command == "login")
        handleLogin(ss);
    else if (command == "logout")
        handleLogout();
    else if (command == "help")
        handleHelp();
    else if (command == "set-goals")
        handleSetGoals(ss);
    else if (command == "log-food")
        handleLogFood(ss);
    else if (command == "log-exercise")
        handleLogExercise(ss);
    else if (command == "log-weight")
        handleLogWeight(ss);
    else if (command == "view-daily-summary")
        handleViewDailySummary();
    else if (command == "view-progress")
        handleViewProgress();
    else if (command == "calculate-bmi")
        handleCalculateBMI();
    else if (command == "calculate-bmr")
        handleCalculateBMR();
    else if (command == "generate-workout-plan")
        handleGenerateWorkoutPlan(ss);
    else if (command == "add-to-favorites")
        handleAddToFavorites(ss);
    else if (command == "view-favorites")
        handleViewFavorites();
    else if (command == "block-user")
        handleBlockUser(ss);
    else if (command == "add-food")
        handleAddFood(ss);
    else if (command == "add-exercise")
        handleAddExercise(ss);
    else if (command == "update-food")
        handleUpdateFood(ss);
    else
        std::cout << "Unknown command: " << command << std::endl;
}

void CalorixUIManager::handleRegister(std::stringstream& ss) {
    std::string username, password, genderStr, activityLevelStr;
    int age, height;
    double weight;

    if (!(ss >> username >> password >> age >> weight >> height >> genderStr >> activityLevelStr)) {
        std::cout << "Usage: register <username> <password> <age> <weight> <height> <Male/Female> <Sedentary/Light/Moderate/Active/VeryActive>" << std::endl;
        return;
    }

    Gender gender = CalorixHelper::parseGenderStr(genderStr);
    ActivityLevel activityLevel = CalorixHelper::parseActivityLevelStr(activityLevelStr);

    _calorix.registerUser(username, password, age, weight, height, gender, activityLevel);

    std::cout << "User '" << username << "' registered and logged in successfully." << std::endl;
}

void CalorixUIManager::handleLogin(std::stringstream& ss) {
    std::string username, password;

    if (!(ss >> username >> password)) {
        std::cout << "Usage: login <username> <password>" << std::endl;
        return;
    }

    _calorix.login(username, password);

    std::cout << "Logged in as '" << username << "'." << std::endl;
}

void CalorixUIManager::handleLogout() {
    _calorix.logout();
    std::cout << "Logged out successfully." << std::endl;
}

void CalorixUIManager::handleHelp() {
    if (!_calorix.isLogged()) {
        std::cout << "Available commands (not logged in):" << std::endl;
        std::cout << "  register <username> <password> <age> <weight> <height> <Male/Female> <Sedentary/Light/Moderate/Active/VeryActive>" << std::endl;
        std::cout << "  login <username> <password>" << std::endl;
        std::cout << "  end" << std::endl;
        return;
    }

    if (_calorix.getLoggedUser()->isAdmin()) {
        std::cout << "Available commands (Admin):" << std::endl;
        std::cout << "  block-user <username>" << std::endl;
        std::cout << "  add-food <name> <calories_per_100g> <protein> <carbs> <fat>" << std::endl;
        std::cout << "  add-exercise <name> <calories_per_hour> <duration_minutes> <muscle_group_id>" << std::endl;
        std::cout << "  update-food <name> <new_calories>" << std::endl;
        std::cout << "  logout" << std::endl;
        std::cout << "  end" << std::endl;
    }
    else {
        std::cout << "Available commands (Trainee):" << std::endl;
        std::cout << "  set-goals <WeightLoss/Bulking/Maintenance> <target_value> <deadline (DD/MM/YYYY)>" << std::endl;
        std::cout << "  log-food <food_name> <quantity_grams>" << std::endl;
        std::cout << "  log-exercise <exercise_name> <duration_minutes>" << std::endl;
        std::cout << "  log-weight <new_weight>" << std::endl;
        std::cout << "  view-daily-summary" << std::endl;
        std::cout << "  view-progress" << std::endl;
        std::cout << "  calculate-bmi" << std::endl;
        std::cout << "  calculate-bmr" << std::endl;
        std::cout << "  generate-workout-plan <duration_minutes>" << std::endl;
        std::cout << "  add-to-favorites <exercise_name>" << std::endl;
        std::cout << "  view-favorites" << std::endl;
        std::cout << "  logout" << std::endl;
        std::cout << "  end" << std::endl;
    }
}

void CalorixUIManager::handleSetGoals(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::string goalTypeStr;
    std::string targetTypeStr;
    double targetValue;
    std::string dateStr;

    if (!(ss >> goalTypeStr >> targetTypeStr >> targetValue >> dateStr)) {
        std::cout << "Usage: set-goals <WeightLoss/Bulking/Maintenance> <Weight/Calories> <target_value> <DD-MM-YYYY>" << std::endl;
        return;
    }

    int day, month, year;
    if (sscanf_s(dateStr.c_str(), "%d-%d-%d", &day, &month, &year) != 3) {
        std::cout << "Invalid date format. Use DD-MM-YYYY (e.g. 31-12-2025)" << std::endl;
        return;
    }

    std::tm tm = {};
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_hour = 23;
    tm.tm_min = 59;
    tm.tm_sec = 59;
    tm.tm_isdst = -1;

    time_t deadline = std::mktime(&tm);

    if (deadline == -1) {
        std::cout << "Could not convert date to timestamp. Check the date is valid." << std::endl;
        return;
    }

    GoalType goalType = CalorixHelper::parseGoalStr(goalTypeStr);
    TargetType targetType = CalorixHelper::parseTargetTypeStr(targetTypeStr);

    trainee->setGoals(goalType, targetType, targetValue, deadline);

    std::cout << "Goals set successfully." << std::endl;
}

void CalorixUIManager::handleLogFood(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::string rest;
    std::getline(ss, rest);

    int lastSpace = rest.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        std::cout << "Usage: log-food <food_name> <quantity_grams>" << std::endl;
        return;
    }

    std::string foodName = rest.substr(0, lastSpace);
    if (!foodName.empty() && foodName[0] == ' ')
        foodName = foodName.substr(1);

    int quantity;
    try {
        quantity = std::stoi(rest.substr(lastSpace + 1));
    }
    catch (...) {
        std::cout << "Usage: log-food <food_name> <quantity_grams>" << std::endl;
        return;
    }

    auto result = trainee->logFood(foodName, quantity);

    if (result)
        std::cout << std::format("{} logged in your food diary.", foodName);
    else
        std::cout << result.error();

    std::cout << std::endl;
}

void CalorixUIManager::handleLogExercise(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::string rest;
    std::getline(ss, rest);

    size_t lastSpace = rest.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        std::cout << "Usage: log-exercise <exercise_name> <duration_minutes>" << std::endl;
        return;
    }

    std::string exerciseName = rest.substr(0, lastSpace);
    if (!exerciseName.empty() && exerciseName[0] == ' ')
        exerciseName = exerciseName.substr(1);

    int duration;
    try {
        duration = std::stoi(rest.substr(lastSpace + 1));
    }
    catch (...) {
        std::cout << "Usage: log-exercise <exercise_name> <duration_minutes>" << std::endl;
        return;
    }

    auto result = trainee->logExercise(exerciseName, duration);

    if (result)
        std::cout << std::format("{} logged in your exercise diary.", exerciseName);
    else
        std::cout << result.error();

    std::cout << std::endl;
}

void CalorixUIManager::handleLogWeight(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    double newWeight;
    if (!(ss >> newWeight)) {
        std::cout << "Usage: update-weight <new_weight>" << std::endl;
        return;
    }

    trainee->logWeight(newWeight);

    std::cout << "Weight successfully updated to " << newWeight << " kg." << std::endl;
}

void CalorixUIManager::handleViewDailySummary() {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::cout << trainee->viewDailySummary();
}

void CalorixUIManager::handleViewProgress() {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::cout << trainee->viewProgress() << std::endl;
}

void CalorixUIManager::handleCalculateBMI() {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    double bmi = trainee->calculateBMI();

    std::cout << std::format("BMI: {}", bmi) << std::endl;
}

void CalorixUIManager::handleCalculateBMR() {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    double bmr = trainee->calculateBMR();

    std::cout << std::format("BMR: {}", bmr) << std::endl;
}

void CalorixUIManager::handleGenerateWorkoutPlan(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    int duration;
    if (!(ss >> duration)) {
        std::cout << "Usage: generate-workout-plan <duration_minutes>" << std::endl;
        return;
    }

    std::vector<const Exercise*> plan = trainee->generateWorkoutPlan(duration);

    if (plan.empty()) {
        std::cout << "No exercises fit within " << duration << " minutes." << std::endl;
        return;
    }

    std::cout << "--- Workout Plan (" << duration << " min) ---" << std::endl;

    int totalCalories = 0;
    for (const Exercise* ex : plan) {
        std::cout << *ex << std::endl;
        totalCalories += ex->getCaloriesForSuggestedDuration();
    }

    std::cout << "Total estimated calories burned: " << totalCalories << " kcal" << std::endl;
}

void CalorixUIManager::handleAddToFavorites(std::stringstream& ss) {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::string exerciseName;
    std::getline(ss, exerciseName);

    if (!exerciseName.empty() && exerciseName[0] == ' ')
        exerciseName = exerciseName.substr(1);

    if (exerciseName.empty()) {
        std::cout << "Usage: add-to-favorites <exercise_name>" << std::endl;
        return;
    }

    auto result = trainee->addToFavorites(exerciseName);

    if (result)
        std::cout << "Exercise '" + exerciseName + "' was successfully added to your Favorites.";
    else
        std::cout << result.error();

    std::cout << std::endl;
}

void CalorixUIManager::handleViewFavorites() {
    Trainee* trainee = getLoggedTrainee();
    if (trainee == nullptr) {
        std::cout << "This command is only available for Trainee users." << std::endl;
        return;
    }

    std::cout << trainee->viewFavorites();
}

void CalorixUIManager::handleBlockUser(std::stringstream& ss) {
    std::string username;

    if (!(ss >> username)) {
        std::cout << "Usage: block-user <username>" << std::endl;
        return;
    }

    _calorix.blockUser(username);
    std::cout << "User '" << username << "' has been blocked." << std::endl;
}

void CalorixUIManager::handleAddFood(std::stringstream& ss) {
    std::string rest;
    std::getline(ss, rest);

    std::vector<std::string> tokens;
    std::string current;

    for (int i = rest.size() - 1; i >= 0; i--) {
        if (rest[i] == ' ') {
            if (!current.empty()) {
                tokens.push_back(current);
                current = "";
                if (tokens.size() == 4) {
                    std::string name = rest.substr(0, i);
                    if (!name.empty() && name[0] == ' ')
                        name = name.substr(1);
                    tokens.push_back(name);
                    break;
                }
            }
        }
        else {
            current = rest[i] + current;
        }
    }

    if (tokens.size() < 5) {
        std::cout << "Usage: add-food <name> <calories_per_100g> <protein_per_100g> <carbs_per_100g> <fat_per_100g>" << std::endl;
        return;
    }

    try {
        std::string name = tokens[4];
        int calories = std::stoi(tokens[3]);
        int protein = std::stoi(tokens[2]);
        int carbs = std::stoi(tokens[1]);
        int fat = std::stoi(tokens[0]);

        _calorix.addFood(name, calories, protein, carbs, fat);
        std::cout << "Food '" << name << "' added successfully." << std::endl;
    }
    catch (...) {
        std::cout << "Usage: add-food <name> <calories_per_100g> <protein> <carbs> <fat>" << std::endl;
    }
}

void CalorixUIManager::handleAddExercise(std::stringstream& ss) {
    Admin* admin = getLoggedAdmin();
    if (admin == nullptr) {
        std::cout << "This command is only available for Admin users." << std::endl;
        return;
    }

    std::string rest;
    std::getline(ss, rest);

    std::vector<std::string> tokens;
    std::string current;

    for (int i = rest.size() - 1; i >= 0; i--) {
        if (rest[i] == ' ') {
            if (!current.empty()) {
                tokens.push_back(current);
                current = "";
                if (tokens.size() == 3) {
                    std::string name = rest.substr(0, i);
                    if (!name.empty() && name[0] == ' ')
                        name = name.substr(1);
                    tokens.push_back(name);
                    break;
                }
            }
        }
        else {
            current = rest[i] + current;
        }
    }

    if (tokens.size() < 4) {
        std::cout << "Usage: add-exercise <name> <calories_per_hour> <duration_minutes> <muscle_group>" << std::endl;
        return;
    }

    try {
        std::string name = tokens[3];
        int calories = std::stoi(tokens[2]);
        int duration = std::stoi(tokens[1]);
        std::string muscleGroup = tokens[0];

        admin->addExercise(name, calories, duration, muscleGroup);
        std::cout << "Exercise '" << name << "' added successfully." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void CalorixUIManager::handleUpdateFood(std::stringstream& ss) {
    std::string rest;
    std::getline(ss, rest);

    size_t lastSpace = rest.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        std::cout << "Usage: update-food <food_name> <new_calories>" << std::endl;
        return;
    }

    std::string foodName = rest.substr(0, lastSpace);
    if (!foodName.empty() && foodName[0] == ' ')
        foodName = foodName.substr(1);

    int newCalories;
    try {
        newCalories = std::stoi(rest.substr(lastSpace + 1));
    }
    catch (...) {
        std::cout << "Usage: update-food <food_name> <new_calories>" << std::endl;
        return;
    }

    _calorix.updateFood(foodName, newCalories);
    std::cout << "Food '" << foodName << "' updated successfully." << std::endl;
}
