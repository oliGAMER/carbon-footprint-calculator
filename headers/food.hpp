
#pragma once
#include "activity.hpp"

class Food : public Activity
{
private:
    double weeklyConsumptionKg;

public:
    Food(double d);
    void setWeeklyConsumption(double kg);
    double getWeeklyConsumption();
    double calculateEmission() override;
    ~Food();
};
