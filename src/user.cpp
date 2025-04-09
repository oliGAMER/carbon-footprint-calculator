#include <iostream>
#include <fstream>
#include "..\headers\user.hpp"

#include "..\headers\activity.hpp"

User::User(std::string name, std::string location)
    : transport(0.0), food(0.0), electricity(0.0), totalCarbonFootprint(0.0),
      name(name), location(location) {}


      User::User(std::string name, std::string location, double foodConsumption, double electricityConsumption, double transportDistance)
      : transport(transportDistance), food(foodConsumption), electricity(electricityConsumption),
        totalCarbonFootprint(0.0), name(name), location(location) {}
  

void User::setTransportData(double distance)
{
    transport.setDistance(distance);
}

void User::setFoodData(double weeklyConsumption)
{
    food.setWeeklyConsumption(weeklyConsumption);
}

void User::setElectricityData(double monthlyKwh)
{
    electricity.setMonthlyUsage(monthlyKwh);
}

void User::calculateCarbonFootprint()
{
    totalCarbonFootprint =
        transport.calculateEmission() +
        food.calculateEmission() +
        electricity.calculateEmission();
}

double User::getTotalCarbonFootprint() const
{
    return totalCarbonFootprint;
}

void User::display() const
{
    std::cout << "User: " << name << ", Location: " << location << "\n";
    std::cout << "Total Carbon Footprint: " << totalCarbonFootprint << " kg CO2\n";
}

void User::saveToCSV(const std::string &filename) const
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        file << name << "," << location << "," << totalCarbonFootprint << "\n";
        file.close();
    }
}

void User::setEmission(double transportEmissions, double foodEmissions, double electricityEmissions)
{
    transport.setDistance(transportEmissions);
    food.setWeeklyConsumption(foodEmissions);
    electricity.setMonthlyUsage(electricityEmissions);
    totalCarbonFootprint = food.getWeeklyConsumption() + electricity.getMonthlyUsage() + transport.getDistance();
}
User::~User(){}