# Carbon Footprint Calculator

## Overview
This C++ application calculates an individual's carbon footprint based on their electricity usage, food consumption habits, and transportation activities. It features data storage in CSV format, geocoding of user locations, interactive map generation for location confirmation and emission "red zone" visualization, and statistical analysis of collected data.

## Features
- Calculates carbon emissions from:
    - Electricity (kWh)
    - Food (based on a carbon factor or weekly consumption)
    - Transport (distance in km)
- User input for name, location, and consumption data.
- Saves user data (name, location, total emissions) to `user_data.csv`.
- Geocodes locations using the Nominatim OpenStreetMap API.
- **Location Confirmation:** Generates `user_data.js` and `map.html` to allow users to visually confirm their geocoded location.
- **Red Zone Mapping:** Generates `zone_data.js` and `map_red_zones.html` showing geographical clusters of users and highlighting "red zones" with high aggregate emissions. This reads from `user_data.csv`.
- **Statistical Analysis:** Calculates and displays mean, median, standard deviation, variance, and IQR for emissions data from `user_data.csv`.
- **Emission Classification:** Classifies a user's total emission as Low, Medium, or High.
- Command-Line Interface (CLI).

## Tech Stack
- C++ (C++17 recommended)
- CMake (for building the project)
- External Libraries:
    - **libcurl:** For making HTTP requests to the Nominatim API.
    - **nlohmann/json:** For parsing JSON responses from the Nominatim API.
- HTML/JavaScript: For map visualizations (requires a modern web browser).

## Directory Structure

```text
.
├── CMakeLists.txt                  // Main CMake configuration file
├── build/                          // Build output directory
│   ├── CarbonFootprintCalculator.exe // The compiled executable
│   ├── map.html                      // HTML file for single user location map
│   ├── map_red_zones.html            // HTML file for red zone emission map
│   ├── user_data.csv                 // Stores user emission data
│   ├── user_data.js                  // JavaScript data for map.html
│   └── zone_data.js                  // JavaScript data for map_red_zones.html
├── headers/
│   ├── .gitkeep
│   ├── activity.hpp
│   ├── csv_reader.hpp
│   ├── electricity.hpp
│   ├── emission_classifier.hpp
│   ├── food.hpp
│   ├── GeoEncoder.hpp
│   ├── statistics.hpp
│   ├── transport.hpp
│   └── user.hpp
├── main/
│   ├── .gitkeep
│   └── t.cpp (main.cpp)
└── src/
    ├── .gitkeep
    ├── csv_reader.cpp
    ├── electricity.cpp
    ├── food.cpp
    ├── GeoEncoder.cpp
    ├── statistics.cpp
    ├── transport.cpp
    └── user.cpp

*(Important: While `user_data.csv`, `user_data.js` and `zone_data.js` are automatically generated, you must manually copy `map.html` and `map_red_zones.html` to your build/working directory for the mapping functionality to work properly. These HTML files should be placed in the same directory as the executable.)*
```
## Prerequisites
- A C++ compiler supporting C++17 (e.g., GCC, Clang, MSVC).
- CMake (version 3.10 or higher).
- libcurl development libraries.
- nlohmann/json header-only library (typically placed in a system include path or managed via CMake's `FetchContent` or as a submodule).
- Internet connection (for geocoding and map tile fetching by the HTML maps).

## Building the Project (Example with CMake)
1.  **Clone the repository (if applicable) or ensure you have all project files.**
2.  **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```
3.  **Configure the project using CMake:**
    (This step tells CMake to look for `CMakeLists.txt` in the parent directory `..`)
    ```bash
    cmake ..
    ```
    *   If CMake cannot find libcurl or nlohmann/json automatically, you might need to provide hints:
        *   For libcurl: `-DCURL_INCLUDE_DIR=/path/to/curl/include -DCURL_LIBRARY=/path/to/curl/lib/libcurl.so` (paths vary by system).
        *   For nlohmann/json (if not found by default): Ensure it's in your include path, or adapt your `CMakeLists.txt` to find/fetch it.
4.  **Build the project:**
    ```bash
    cmake --build .
    ```
    Alternatively, on Linux/macOS, you can often use:
    ```bash
    make
    ```
5.  The executable (e.g., `CarbonFootprintCalculator.exe` on Windows, or `CarbonFootprintCalculator` on Linux/macOS) will be located in the `build` directory.

## Usage
1.  Navigate to the `build` directory in your terminal (if not already there).
2.  Run the executable:
    *   On Windows: `.\CarbonFootprintCalculator.exe`
    *   On Linux/macOS: `./CarbonFootprintCalculator`
3.  Follow the on-screen menu options:
    *   **1-3:** Enter data for transport, food, and electricity emissions.
    *   **4:** View your calculated total carbon footprint.
    *   **5:** Save your current data to `user_data.csv` (located in the `build` directory or where the executable is run). This is important before using map features for the current user.
    *   **6:** Exit the application.
    *   **7:** Enter/confirm your location. This will generate/update `user_data.js` and attempt to open `map.html` in your default browser for visual confirmation.
    *   **8:** Generate `zone_data.js` from all entries in `user_data.csv` and attempt to open `map_red_zones.html` to view emission clusters.
    *   **9:** View statistical analysis of data in `user_data.csv` and your current emission classification.

## Notes
- The `map.html` and `map_red_zones.html` files use Leaflet.js and OpenStreetMap tiles for mapping. An internet connection is required for the maps to load correctly in your browser.
- Ensure you save your data (Option 5) before attempting to generate maps for the current session's user (Option 7). Option 8 always reads from the existing `user_data.csv`.
- The files `lib.cpp` and `t.cpp` in the `main/` directory are part of the project structure; their specific roles should be detailed if they contain significant logic.
