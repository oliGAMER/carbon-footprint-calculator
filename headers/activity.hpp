#pragma once

class Activity
{

public:
    virtual double calculateEmission() = 0;
    virtual ~Activity() = default;
};