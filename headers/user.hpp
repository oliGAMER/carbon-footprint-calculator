
#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "activity.hpp"
#include "transport.hpp"
#include "food.hpp"
#include "electricity.hpp"

class User
{
private:
    std::string name;
    std::string location;

    Transport transport;
    Food food;
    Electricity electricity;

    double totalCarbonFootprint;

public:
    User(std::string name, std::string location);
    User(std::string name, std::string location, double foodConsumption, double electricityConsumption, double transportDistance);
    void setTransportData(double distance);
    void setFoodData(double weeklyConsumption);
    void setElectricityData(double monthlyKwh);

    void calculateCarbonFootprint();
    double getTotalCarbonFootprint() const;
    ~User();
    void display() const;
    void saveToCSV(const std::string &filename) const;
    void setEmission(double transportEmissions, double foodEmissions, double electricityEmissions);
};