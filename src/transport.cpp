#include "..\headers\transport.hpp"
#include <iostream>

Transport::Transport(double d) : distance(d) {}

double Transport::getDistance()
{
    return distance;
}
void Transport::setDistance(double d)
{
    distance = d;
}

double Transport::calculateEmission()
{
    double co2_per_km = 0.12;
    return co2_per_km * distance;
}

void Transport::display()
{
    std::cout << "Transport Distance: " << distance << " km" << std::endl;
    std::cout << "CO2 Emission: " << calculateEmission() << " kg" << std::endl;
}
Transport::~Transport()
{
}