cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CHIP8)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Get the project's source files
file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.h)

# Create the project
add_executable(CHIP8 ${SRC_FILES})

# Set the project's include directories
target_include_directories(CHIP8 PUBLIC src)

# Add the necessary link libraries