#include "../headers/geoencoder.hpp"
#include <curl/curl.h>
//for string formatting, such as the ostringstream stuff
#include <sstream>
//provides formatting manipulators for input/output operations
#include <iomanip>
#include <iostream>

GeoEncoder::GeoEncoder() {
    apiUrl = "https://nominatim.openstreetmap.org/search";
}

std::string GeoEncoder::urlEncode(const std::string& value) {
    std::ostringstream escaped; // to store the encoded string
    for (char c : value) {
        // if the character is one of these, considered safe
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            // if not safe makes a two digit hex value where the letter will be capital
            escaped << '%' << std::uppercase << std::hex << std::setw(2)
                    << std::setfill('0') << int((unsigned char)c);
        }
    }
    // to recieve the final string that has been constructed
    return escaped.str();
}

size_t GeoEncoder::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    // void* contents is a pointer to the data received from the server
    // size is the size of each element in the data received
    // nmemb is the number of elements received
    // output is a pointer to the string where the data will be stored
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

GeoEncoder::Coordinates GeoEncoder::getCoordinates(const std::string& area,
                                                 const std::string& city,
                                                 const std::string& country) {
    std::string fullAddress = area + ", " + city + ", " + country;
    std::string encodedAddress = urlEncode(fullAddress);
    
    Coordinates coords = {0.0, 0.0, false, "Location not found"};
    
    std::string url = apiUrl + "?q=" + encodedAddress + "&format=json&limit=1";
    
    CURL* curl = curl_easy_init();
    if (!curl) {
        coords.message = "CURL initialization failed";
        return coords;
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "C++NominatimClient/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    //prevents memory leaks
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
        try {
            auto jsonData = nlohmann::json::parse(response);
            if (!jsonData.empty()) {
                coords.latitude = std::stod(jsonData[0]["lat"].get<std::string>());
                coords.longitude = std::stod(jsonData[0]["lon"].get<std::string>());
                coords.isValid = true;
                coords.message = "Location found";
            }
        } catch (std::exception& e) {
            coords.message = "Failed to parse JSON: " + std::string(e.what());
        }
    } else {
        coords.message = "Failed to connect to geocoding service";
    }

    return coords;
}