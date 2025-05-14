#!/bin/bash
cd "$(dirname "$0")"
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build 
./build/CarbonFootprintCalculator.exe
