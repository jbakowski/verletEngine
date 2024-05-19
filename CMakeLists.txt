# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Project name and the languages used
project(physics_sim LANGUAGES CXX)

# Output directory for the runtime files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add SFML as a subdirectory
add_subdirectory(SFML-2.6.x)

file(GLOB SOURCES "src/*.cpp" "src/engine/*.cpp" "src/renderer/*.cpp" "src/utils/*cpp")

# Add an executable file to the project
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "include" "include/engine" "include/renderer" "include/utils")

# Link the SFML graphics library to the project
target_link_libraries(${PROJECT_NAME} sfml-graphics)

# Set the C++ standard to be used in the project
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Install the targets
install(TARGETS ${PROJECT_NAME})