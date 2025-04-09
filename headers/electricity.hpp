#include "activity.hpp"
#include <iostream>
#pragma once

class Electricity : public Activity
{

    double Usage;

public:
    Electricity(double d);
    void setMonthlyUsage(double kwh);
    double getMonthlyUsage() const;
    double calculateEmission() override;
    ~Electricity();
};