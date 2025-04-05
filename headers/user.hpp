
#pragma once
using namespace std;
#include <iostream>

class User
{
    string name;
    string location;
    double transport, food, electricity;

public:
    User(std::string n, std::string loc);
    void setEmissions(double t, double f, double e);
    double getTotalEmission() const;
    void display() const;
    void saveToCSV(const std::string &filename = "userdata.csv") const;
};