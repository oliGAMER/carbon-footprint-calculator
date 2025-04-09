#pragma once
#include "activity.hpp"

class Transport : public Activity
{
private:
    double distance;

public:
    Transport(double d);
    ~Transport();
    double getDistance();
    double calculateEmission();
    void setDistance(double d);
    void display();
};
