#ifndef GEOENCODER_HPP
#define GEOENCODER_HPP

#include <string>
#include <nlohmann/json.hpp>

class GeoEncoder {
private:
    std::string apiUrl;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    std::string urlEncode(const std::string& value);

public:
    GeoEncoder();
    
    struct Coordinates {
        double latitude;
        double longitude;
        bool isValid;
        std::string message;
    };

    Coordinates getCoordinates(const std::string& area, 
                             const std::string& city, 
                             const std::string& country);
};

#endif // GEOENCODER_HPP