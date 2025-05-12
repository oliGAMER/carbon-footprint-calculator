#pragma once
#include <iostream>
//Fully defined in the header file 
// wont be able to generate code for other types unless explicitly instantiated
template <typename T>
class EmissionClassifier {
private:
    T lowThreshold, highThreshold;
public:
    EmissionClassifier(T low, T high) : lowThreshold(low), highThreshold(high) {}
    
    void operator()(T emission) const {
        if (emission < lowThreshold) {
            std::cout << "Low Emission\n";
        } else if (emission >= lowThreshold && emission <= highThreshold) {
            std::cout << "Medium Emission\n";
        } else {
            std::cout << "High Emission\n";
        }
    }
};