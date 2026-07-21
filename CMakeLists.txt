cmake_minimum_required(VERSION 3.14)

project(
    TurretProject
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Adding compiler warnings per NASA JPL Rule 10 Alignment
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/shared
    ${CMAKE_CURRENT_SOURCE_DIR}/turret_Uno
    ${CMAKE_CURRENT_SOURCE_DIR}/vision_Pi
)

# Target 1: Unit Test Runner Executable
add_executable(
    run_tests
    unit_testing/test_command_parser.cpp
    unit_testing/test_target_resolver.cpp
)

# Target 2: Main Turret Control Executable 
# add_executable(
#    vision_Pi
#    vision_Pi/main.cpp
#)