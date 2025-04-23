// csv_reader.cpp
#include "..\headers\csv_reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<CSVUserRecord> CSVReader::readZones(const std::string &filename)
{
    std::vector<CSVUserRecord> zones;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open " << filename << "\n";
        return zones;
    }

    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, location, emissionStr;
        std::getline(ss, name, ',');
        if (ss.peek() == '"')
        {
            ss.get();
            std::getline(ss, location, '"');
            if (ss.peek() == ',')
                ss.get();
        }
        else
        {
            std::getline(ss, location, ',');
        }
        std::getline(ss, emissionStr);

        try
        {
            double emission = std::stod(emissionStr);
            zones.push_back({name, location, emission});
        }
        catch (...)
        {
            std::cout << "Error parsing emission for: " << location << "\n";
        }
    }

    return zones;
}
