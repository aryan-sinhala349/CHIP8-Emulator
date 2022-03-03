#Add source files
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    Emulator/Emulator.h
    Emulator/Emulator.cpp
)

#Include project header files
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})