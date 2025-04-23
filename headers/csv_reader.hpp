// csv_reader.hpp
#pragma once
#include <string>
#include <vector>

struct CSVUserRecord
{
    std::string name;
    std::string location;
    double emission;
};

class CSVReader
{
public:
    static std::vector<CSVUserRecord> readZones(const std::string &filename);
};
