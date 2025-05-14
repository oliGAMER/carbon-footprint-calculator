cmake_minimum_required(VERSION 3.14)
project(CarbonFootprintCalculator)

set(CMAKE_CXX_STANDARD 17)

# Include project headers
include_directories(headers)

# Find system packages
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Collect source files
file(GLOB SOURCES
    main/*.cpp
    src/*.cpp
)

# Build the executable
add_executable(CarbonFootprintCalculator ${SOURCES})

# Link libraries
target_link_libraries(CarbonFootprintCalculator PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)
