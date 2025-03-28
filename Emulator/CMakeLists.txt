# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(NOSComputer)

# Set the C++ standard (optional but recommended)
# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")  # Disable optimizations for easier debugging
set(CMAKE_CXX_STANDARD 23)   # You can also set 14 or 20 depending on your needs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Generate a Compile Commands json for ClangD lsp

# Library packages that are needed
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Define where to find header files (optional)
# You can add paths to third-party libraries here, like if you're using an external math library
include_directories(headers)

# Collect all source files in the 'src' folder (You can also list them manually)
file(GLOB SOURCES src/*.cpp)

# Create the executable
add_executable(NOSComputerEmulator ${SOURCES})
target_link_libraries(NOSComputerEmulator ${CURSES_LIBRARIES} ncurses)
