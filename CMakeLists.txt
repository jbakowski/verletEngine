# Minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Project name and the languages used
project(physics_sim LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the VCPKG toolchain file
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

# Output directory for the runtime files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find packages using VCPKG
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(imgui REQUIRED)
find_package(ImGui-SFML REQUIRED)

file(GLOB SOURCES "src/*.cpp" "src/engine/*.cpp" "src/renderer/*.cpp" "src/utils/*.cpp")

# Add an executable file to the project
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE "include" "include/engine" "include/renderer" "include/utils")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system imgui::imgui ImGui-SFML::ImGui-SFML)

# Install the targets
install(TARGETS ${PROJECT_NAME})