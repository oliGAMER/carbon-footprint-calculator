#include "../headers/food.hpp"

Food::Food(double d) : weeklyConsumptionKg(d) {}

void Food::setWeeklyConsumption(double kg)
{
    weeklyConsumptionKg = kg;
}

double Food::getWeeklyConsumption()
{
    return weeklyConsumptionKg;
}

double Food::calculateEmission()
{
    return weeklyConsumptionKg * 2.5;
}
Food::~Food() {}