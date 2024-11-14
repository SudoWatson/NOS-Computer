#!/bin/bash

# Create the build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to configure the project and generate Makefiles
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Compile the project using Make
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build succeeded!"
    # Run the executable
    ./NOSComputerEmulator
else
    echo "Build failed."
fi

