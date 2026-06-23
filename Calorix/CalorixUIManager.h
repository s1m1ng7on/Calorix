#pragma once
#include <string>
#include <sstream>
#include "Trainee.h"
#include "Admin.h"

class Calorix;

class CalorixUIManager {
private:
    Calorix& _calorix;

    Trainee* getLoggedTrainee() const;
    Admin* getLoggedAdmin() const;

    void executeCommand(const std::string& command, std::stringstream& ss);

    void handleRegister(std::stringstream& ss);
    void handleLogin(std::stringstream& ss);
    void handleLogout();
    void handleHelp();

    void handleSetGoals(std::stringstream& ss);
    void handleLogFood(std::stringstream& ss);
    void handleLogExercise(std::stringstream& ss);
    void handleLogWeight(std::stringstream& ss);
    void handleViewDailySummary();
    void handleViewProgress();
    void handleCalculateBMI();
    void handleCalculateBMR();
    void handleGenerateWorkoutPlan(std::stringstream& ss);
    void handleAddToFavorites(std::stringstream& ss);
    void handleViewFavorites();

    void handleBlockUser(std::stringstream& ss);
    void handleAddFood(std::stringstream& ss);
    void handleAddExercise(std::stringstream& ss);
    void handleUpdateFood(std::stringstream& ss);

public:
    CalorixUIManager(Calorix& calorix);
    void run();
};
