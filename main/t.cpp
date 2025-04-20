
#include <iostream>
#include "..\headers\user.hpp"
#include "..\headers\transport.hpp"
#include "..\headers\food.hpp"
#include "..\headers\electricity.hpp"
#include "..\headers\GeoEncoder.hpp"  // Add this line
#include <fstream>
#include <limits> 
#include <thread>
#include <chrono>

// #include "../headers/carbon_calculator.hpp"

int main()
{
    //system("start map.html");

    std::string name, location;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your location: ";
    std::getline(std::cin, location);

    User user(name, location);

    double transportEmissions = 0.0;
    double foodEmissions = 0.0;
    double electricityEmissions = 0.0;

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
        std::cout << "7. Enter your location\n";  // Add this line
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
        {
            double distance;
            std::cout << "Enter the distance traveled (in km): ";
            std::cin >> distance;
            Transport transport(distance);
            transportEmissions = transport.calculateEmission();
            std::cout << "Transport Emissions: " << transportEmissions << " kg CO2\n";
            break;
        }
        case 2:
        {
            double foodFactor;
            std::cout << "Enter the food carbon factor: ";
            std::cin >> foodFactor;
            Food food(foodFactor);
            foodEmissions = food.calculateEmission();
            std::cout << "Food Emissions: " << foodEmissions << " kg CO2\n";
            break;
        }
        case 3:
        {
            double consumption;
            std::cout << "Enter electricity consumption (in kWh): ";
            std::cin >> consumption;
            Electricity electricity(consumption);
            electricityEmissions = electricity.calculateEmission();
            std::cout << "Electricity Emissions: " << electricityEmissions << " kg CO2\n";
            break;
        }
        case 4:
        {
            double totalEmissions = transportEmissions + foodEmissions + electricityEmissions;
            std::cout << "Total Carbon Footprint: " << totalEmissions << " kg CO2\n";
            user.setEmission(transportEmissions, foodEmissions, electricityEmissions);
            break;
        }
        case 5:
        {
            user.setEmission(transportEmissions, foodEmissions, electricityEmissions);
            std::string filename = "user_data.csv";
            user.saveToCSV(filename);
            std::cout << "Data saved to " << filename << "\n";
            break;
        }
        case 6:{
            running = false; // to end the program
            std::cout << "Exiting the program.\n";
            break;
        }

        case 7: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            bool locationConfirmed = false;

            while(!locationConfirmed){
                std::string area, city, country;
                std::cout << "Enter country (e.g., Pakistan): ";
                std::getline(std::cin, country);
                std::cout << "Enter city (e.g., Karachi): ";
                std::getline(std::cin, city);
                std::cout << "Enter area (e.g., Gulshan-e-Iqbal): ";
                std::getline(std::cin, area);

                GeoEncoder encoder;
                auto coordinates = encoder.getCoordinates(area, city, country);

                if (coordinates.isValid) {

                    std::ofstream jsFile("user_data.js");
                    if (jsFile.is_open()) {
                        jsFile << "var userData = {\n";
                        jsFile << "  name: \"" << name << "\",\n";
                        jsFile << "  location: [" << coordinates.latitude << ", " << coordinates.longitude << "],\n";
                        jsFile << "};\n";
                        jsFile.close();
                    }

                    std::cout << "\nGenerating the map. Please wait...\n";
                    std::cout << "You have to verify the location and type your response here.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(7)); 

                    system("start map.html");

                    char confirm;
                    std::cout << "\nIs this location correct? (y/n): ";
                    std::cin >> confirm;
            
                    if (confirm == 'y' || confirm == 'Y') {
                        std::cout << "Location confirmed.\n";
                        locationConfirmed = true;


                    } else {
                        std::cout << "Let's try again.\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                } else {
                    std::cout << "\nLocation verification failed!\n";
                    std::cout << "Error: " << coordinates.message << "\n";

                    char tryAgain;
                    std::cout << "Do you want to try a different location? (y/n): ";
                    std::cin >> tryAgain;
        
                    if (tryAgain != 'y' && tryAgain != 'Y') {
                        std::cout << "Skipping location verification.\n";
                        break;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            break;
        }

        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}