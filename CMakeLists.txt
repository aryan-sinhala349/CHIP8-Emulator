#The version of CMake I have installed, feel free to test earlier versions
cmake_minimum_required(VERSION 3.22)

#Set the project details
set(PROJECT_NAME CHIP8)
project(${PROJECT_NAME} LANGUAGES CXX)

#Set the source directory
aux_source_directory("CHIP8 Emulator/src" CHIP8_SRC_LIST)

#Disable in-source builds
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

#Set build type to Debug by default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#Set build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin-int/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin-int/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${PROJECT_BINARY_DIR}/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_BINARY_DIR}/bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${PROJECT_BINARY_DIR}/bin-int/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_BINARY_DIR}/bin-int/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${PROJECT_BINARY_DIR}/bin-int/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${PROJECT_BINARY_DIR}/bin-int/)

#Define the executable
add_executable(${PROJECT_NAME})

#Set C++ standard
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

#Add source files
add_subdirectory("CHIP8 Emulator/src")

#Add third party libraries
add_subdirectory("CHIP8 Emulator/vendor")

#Set compile flags
target_compile_options(${PROJECT_NAME} PRIVATE
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Weverything>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

#Include and link against dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)