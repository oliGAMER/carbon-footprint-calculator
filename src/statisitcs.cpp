#include "../headers/statistics.hpp"
#include <numeric>
#include <algorithm>
#include <cmath>
Statistics::Statistics(const std::vector<CSVUserRecord> &CSVRecords) : records(CSVRecords)
{
    for (const auto &record : records) {
        emissions.push_back(record.emission);
    }

}

double Statistics::calculateMean()
{
    if(records.empty()) {
        return 0.0;
    }
    //Formula: μ = (Σx) / n
    double sum = std::accumulate(emissions.begin(), emissions.end(),0.0);
    return sum / emissions.size();
}

double Statistics::calculateMedian()
{
    if(records.empty()) {
        return 0.0;
    }
    std::sort(emissions.begin(), emissions.end());
    size_t size = emissions.size();
    /*
    For odd n: middle value
    For even n: average of two middle values
    */
    if (size % 2 == 0) {
        return (emissions[size / 2 - 1] + emissions[size / 2]) / 2;
    } else {
        return emissions[size / 2];
    }
}

double Statistics::calculateStandardDeviation()
{
    if(records.empty()) {
        return 0.0;
    }
    ////Formula: σ = √[Σ(x - μ)²/n]
    double mean = calculateMean();
    double sum = std::accumulate(emissions.begin(), emissions.end(), 0.0, [mean](double acc, double val) {
        return acc + (val - mean) * (val - mean);
    });
    return std::sqrt(sum / emissions.size());
}

double Statistics::calculateQuartile(double percentile)
{
    if(records.empty()) {
        return 0.0;
    }
    std::sort(emissions.begin(), emissions.end());
    size_t index = static_cast<size_t>(percentile * (emissions.size() - 1));
    return emissions[index];
}

double Statistics::calculateVariance(){
    double stdDev = calculateStandardDeviation();
    return stdDev * stdDev;
}

double Statistics::calculateIQR(){
    double q1 = calculateQuartile(0.25);
    double q3 = calculateQuartile(0.75);
    return q3 - q1;
}

