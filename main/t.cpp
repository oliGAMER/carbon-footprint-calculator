
#include <iostream>
#include "..\headers\user.hpp"
#include "..\headers\transport.hpp"
#include "..\headers\food.hpp"
#include "..\headers\electricity.hpp"
// #include "../headers/carbon_calculator.hpp"

int main()
{
    // system("start map.html");

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
        case 6:
            running = false;
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }

    return 0;
}
