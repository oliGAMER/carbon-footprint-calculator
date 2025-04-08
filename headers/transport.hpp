#pragma once
#include "activity.hpp"

class Transport : public Activity
{
private:
    double distance;

public:
    Transport(double dist);
    double getDistance();
    double calculateEmission();

    void display();
};
