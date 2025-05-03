#include "../headers/electricity.hpp"

Electricity::Electricity(double d = 0.0) : Usage(d) {}

void Electricity::setMonthlyUsage(double kwh)
{
    Usage = kwh;
}

double Electricity::getMonthlyUsage() const
{
    return Usage;
}

double Electricity::calculateEmission()
{
    return Usage * 0.417;
}
Electricity::~Electricity() {}
