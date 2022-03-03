cmake_minimum_required(VERSION 3.22) #The version of CMake I have installed, feel free to test earlier versions

set(CHIP8_SRC_FILES "CHIP8 Emulator/src/main.cpp")
set(CHIP8_INCLUDE_DIRS "CHIP8 Emulator/src/")

project(CHIP8)

set(CMAKE_CXX_STANDARD 17)
add_executable(CHIP8 ${CHIP8_SRC_FILES})
include_directories(CHIP8 ${CHIP_INCLUDE_DIRS})