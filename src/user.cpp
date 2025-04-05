#include <iostream>
#include <fstream>
#include "..\headers\user.hpp"

User::User(std::string n, std::string loc)
    : name(n), location(loc), transport(0), food(0), electricity(0) {}

void User ::setEmissions(double t, double f, double e)
{
    transport = t;
    food = f;
    electricity = e;
}

double User::getTotalEmission() const
{
    return transport + food + electricity;
}

void User::display() const
{
    std::cout << "Name: " << name << "\nLocation: " << location
              << "\nTransport: " << transport << "\nFood: " << food
              << "\nElectricity: " << electricity
              << "\nTotal CO2 Emission: " << getTotalEmission() << " kg CO2\n";
}

void User::saveToCSV(const std::string &filename) const
{
    std::ofstream outFile(filename, std::ios::app);
    if (outFile.tellp() == 0)
    {
        outFile << "Name,Location,Transport,Food,Electricity,TotalEmission\n";
    }
    outFile << name << "," << location << "," << transport << "," << food << ","
            << electricity << "," << getTotalEmission() << "\n";
    outFile.close();
}