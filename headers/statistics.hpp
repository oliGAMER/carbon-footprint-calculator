#pragma once
#include "csv_reader.hpp"

class Statistics
{
private:
    std::vector<CSVUserRecord> records;
    std::vector<double> emissions;
public:
    Statistics(const std::vector<CSVUserRecord> &CSVRecords);
    double calculateMean();
    double calculateMedian();
    double calculateStandardDeviation();
    double calculateQuartile(double percentile);
    double calculateVariance();
    double calculateIQR();
};
