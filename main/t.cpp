#include <iostream>
#include "../headers/user.hpp"
#include "../headers/transport.hpp"
#include "../headers/food.hpp"
#include "../headers/electricity.hpp"
#include "../headers/GeoEncoder.hpp"
#include "../headers/csv_reader.hpp"
#include "../headers/statistics.hpp"
#include "../headers/emission_classifier.hpp"
#include <fstream>
#include <limits>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <regex>

// helper function to ensure that the emissions are numerical
double getValidatedNumericInput(const std::string& prompt) {
    std::regex numericRegex("^[0-9]*\\.?[0-9]+$"); 
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (std::regex_match(input, numericRegex)) {
            try {
                return std::stod(input); 
            } catch (const std::exception&) {
                std::cout << "Invalid input. Please enter a valid number.\n";
            }
        } else {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
    }
}
//without typedef full type declaration everytime
using StatOperation = double (Statistics::*)();
int main()
{
    std::string name,location,country,city,area;
    while (true) {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    
        if (name.empty()) {
            std::cout << "Name cannot be empty. Please try again.\n";
        } else {
            break; // Exit the loop if the name is valid
        }
    }
    
    do
    {   
        while (true) {
            std::cout << "Enter country: ";
            std::getline(std::cin, country);
            if (country.empty()) {
                std::cout << "Country cannot be empty. Please try again.\n";
                continue;
            }
        
            std::cout << "Enter city: ";
            std::getline(std::cin, city);
            if (city.empty()) {
                std::cout << "City cannot be empty. Please try again.\n";
                continue;
            }
        
            std::cout << "Enter area: ";
            std::getline(std::cin, area);
            if (area.empty()) {
                std::cout << "Area cannot be empty. Please try again.\n";
                continue;
            }
        
            // If all inputs are valid, break out of the loop
            break;
        }

        location = area + ", " + city + ", " + country;

        GeoEncoder encoder;
        auto coordinates = encoder.getCoordinates(area, city, country);

        if (coordinates.isValid)
            break;

        std::cout << coordinates.message << "\nPlease try again.\n";

    } while (true);

    /* std::cout << "Enter country: ";
     std::getline(std::cin, country);
     std::cout << "Enter city: ";
     std::getline(std::cin, city);
     std::cout << "Enter area: ";
     std::getline(std::cin, area);
     location = area + ", " + city + ", " + country;*/

    User user(name, location);
    double transportEmissions = 0.0;
    double foodEmissions = 0.0;
    double electricityEmissions = 0.0;
    bool hasSavedData = false;

    int option = 0;
    bool running = true;

    while (running)
    {
        std::cout << "\n--- Carbon Footprint Calculator ---\n";
        std::cout << "1. Calculate Transport Emissions\n";
        std::cout << "2. Calculate Food Emissions\n";
        std::cout << "3. Calculate Electricity Emissions\n";
        std::cout << "4. View Total Carbon Footprint\n";
        std::cout << "5. Save Data to CSV\n";
        std::cout << "6. Exit\n";
        std::cout << "7. Confirm your location from the map\n";
        std::cout << "8. Generate Red Zone Map\n";
        std::cout << "9. Statistics\n";
        std::cout << "-----------------------------------\n";
        std::cout << "Choose an option: ";

        while (true)
        {
            std::cin >> option;
    
            if (std::cin.fail()) 
            {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a valid integer.\n";
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                break; 
            }
        }

        switch (option)
        {
        case 1:
        {
            double distance = getValidatedNumericInput("Enter the distance traveled (in km): ");
            Transport transport(distance);
            transportEmissions = transport.calculateEmission();
            std::cout << "Transport Emissions: " << transportEmissions << " kg CO2\n";
            break;
        }
        case 2:
        {
            double foodFactor = getValidatedNumericInput("Enter the food carbon factor: ");
            Food food(foodFactor);
            foodEmissions = food.calculateEmission();
            std::cout << "Food Emissions: " << foodEmissions << " kg CO2\n";
            break;
        }
        case 3:
        {
            double consumption = getValidatedNumericInput("Enter electricity consumption (in kWh): ");
            Electricity electricity(consumption);
            electricityEmissions = electricity.calculateEmission();
            std::cout << "Electricity Emissions: " << electricityEmissions << " kg CO2\n";
            break;
        }
        case 4:
        {
            double total = transportEmissions + foodEmissions + electricityEmissions;
            user.setEmission(transportEmissions, foodEmissions, electricityEmissions);
            std::cout << "Total Carbon Footprint: " << total << " kg CO2\n";
            break;
        }
        case 5:
        {
            user.setEmission(transportEmissions, foodEmissions, electricityEmissions);
            user.saveToCSV("user_data.csv");
            hasSavedData = true;
            std::cout << "Data saved.\n";
            break;
        }
        case 6:
            running = false;
            break;

    case 7:
    {
        if (!hasSavedData)
        {
            std::cout << "Please save data first using option 5.\n";
            break;
        }

        bool confirmed = false;
        while (!confirmed)
        {
            std::string area, city, country;
            while (true) {
                std::cout << "Enter country: ";
                std::getline(std::cin, country);
                if (country.empty()) {
                    std::cout << "Country cannot be empty. Please try again.\n";
                    continue;
                }
            
                std::cout << "Enter city: ";
                std::getline(std::cin, city);
                if (city.empty()) {
                    std::cout << "City cannot be empty. Please try again.\n";
                    continue;
                }
            
                std::cout << "Enter area: ";
                std::getline(std::cin, area);
                if (area.empty()) {
                    std::cout << "Area cannot be empty. Please try again.\n";
                    continue;
                }
                break;
            }
            
            std::string fullLocation = area + ", " + city + ", " + country;
            GeoEncoder encoder;
            auto coordinates = encoder.getCoordinates(area, city, country);
            
            if (coordinates.isValid)
            {
                double totalEmissions = transportEmissions + foodEmissions + electricityEmissions;
                std::ofstream js("user_data.js");
                js << "var userData = {\n";
                js << "  name: \"" << name << "\",\n";
                js << "  location: [" << coordinates.latitude << ", " << coordinates.longitude << "],\n";
                js << "  locationText: \"" << fullLocation << "\",\n"; 
                js << "  totalEmissions: " << totalEmissions << "\n";
                js << "};\n";
                js.close();

                std::cout << "Opening map...\n";
                std::this_thread::sleep_for(std::chrono::seconds(4));
                system("start map.html");

                std::cout << "Is location correct? (y/n): ";
                char check;
                std::cin >> check;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (check == 'y' || check == 'Y')
                {
                    confirmed = true;
                    std::cout << "Location updated successfully.\n";
                }

                else{
                    std::cout << "Location not confirmed. Please try again.\n";
                }
            }
            else
            {
                std::cout << "Location failed: " << coordinates.message << "\n";
                std::cout << "Retry? (y/n): ";
                char retry;
                std::cin >> retry;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (retry != 'y' && retry != 'Y')
                    break;
                
            }
        }
        break;
    }

        case 8:
        {
            // if (!hasSavedData)
            //          {
            //         std::cout << "Please save data first using option 5.\n";
            //          break;
            //    }

            const double RED_ZONE_THRESHOLD = 500.0;
            std::vector<CSVUserRecord> records = CSVReader::readZones("user_data.csv");
            GeoEncoder encoder;

            struct UserPoint
            {
                std::string name;
                std::string location;
                double lat, lon;
                double emission;
            };

            std::vector<UserPoint> allUsers;
            for (const auto &rec : records)
            {
                auto coords = encoder.getCoordinates("", "", rec.location);
                if (coords.isValid)
                {
                    allUsers.push_back({rec.name, rec.location, coords.latitude, coords.longitude, rec.emission});
                }
            }

            auto haversine = [](double lat1, double lon1, double lat2, double lon2)
            {
                const double R = 6371000.0, toRad = acos(-1) / 180.0;
                double dLat = (lat2 - lat1) * toRad, dLon = (lon2 - lon1) * toRad;
                double a = sin(dLat / 2) * sin(dLat / 2) +
                           cos(lat1 * toRad) * cos(lat2 * toRad) * sin(dLon / 2) * sin(dLon / 2);
                return R * 2 * atan2(sqrt(a), sqrt(1 - a));
            };
            // same size as the all users vector, all elements are false
            // this vector is used to mark which users have been grouped
            std::vector<bool> grouped(allUsers.size(), false);
            // stores all the groups of users
            // each group is a vector of UserPoint objects
            std::vector<std::vector<UserPoint>> groups;

            for (size_t i = 0; i < allUsers.size(); ++i)
            {
                if (grouped[i])
                    continue;
                //the     
                // current user is not grouped, so we start a new group
                // create a new group and add the current user to it
                std::vector<UserPoint> group;
                std::queue<size_t> q;
                q.push(i);
                grouped[i] = true;

                while (!q.empty())
                {   
                    //retrieves the position of the user in the queue
                    size_t idx = q.front();
                    q.pop();
                    // adds the user to the group
                    group.push_back(allUsers[idx]);

                    for (size_t j = 0; j < allUsers.size(); ++j)
                    {
                        if (!grouped[j] && haversine(allUsers[idx].lat, allUsers[idx].lon, allUsers[j].lat, allUsers[j].lon) < 5000)
                        {
                            // if the user is not grouped and is within 5km of the current user, add them to the group
                            grouped[j] = true;
                            q.push(j);
                        }
                    }
                }
                //push that group back to the groups vector
                groups.push_back(group);
            }

            std::ofstream js("zone_data.js");
            js << "var zoneData = [\n";
            for (size_t i = 0; i < groups.size(); ++i)
            {
                const auto &group = groups[i];
                double totalEmission = 0;
                std::string combinedNames;
                for (const auto &user : group)
                {
                    totalEmission += user.emission;
                    combinedNames += user.name + " (" + user.location + "), ";
                }
                if (!combinedNames.empty())
                    combinedNames.pop_back(), combinedNames.pop_back();

                const auto &center = group[0];
                bool isRed = totalEmission > RED_ZONE_THRESHOLD;

                js << "  {\n";
                js << "    name: \"" << combinedNames << "\",\n";
                js << "    coords: [" << center.lat << ", " << center.lon << "],\n";
                js << "    totalEmission: " << std::fixed << std::setprecision(2) << totalEmission << ",\n";
                js << "    isRedZone: " << (isRed ? "true" : "false") << "\n";
                js << "  }" << (i < groups.size() - 1 ? "," : "") << "\n";
            }
            js << "];";
            js.close();
            std::cout << "Red zone map generated. Opening map...\n";
            system("start map_red_zones.html");
            break;
        }
        case 9:
        {
            EmissionClassifier<double> classifier(0.0, 500.0);
            double total = transportEmissions + foodEmissions + electricityEmissions;
            std::cout << std::endl;
            std::cout << "Emission Classification: ";
            classifier(total);
            std::cout << std::endl;
            std::vector<CSVUserRecord> records = CSVReader::readZones("user_data.csv");
            Statistics stats(records);
            StatOperation operations[] = {
                &Statistics::calculateMean,
                &Statistics::calculateMedian,
                &Statistics::calculateStandardDeviation,
                &Statistics::calculateVariance,
                &Statistics::calculateIQR
            };
            
            // Define corresponding names
            const char* names[] = {
                "Mean",
                "Median",
                "Standard Deviation",
                "Variance",
                "IQR"
            };

            std::cout <<"\nStatiscal Analysis\n";
            std::cout << "-------------------\n";

            for(size_t i = 0; i < 5; ++i) {
            double result = (stats.*operations[i])();
            std::cout << std::setw(20) << std::left << names[i] 
                 << ": " << std::fixed << std::setprecision(2) << result << "\n";
            }
            break;
        }

        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }
}
