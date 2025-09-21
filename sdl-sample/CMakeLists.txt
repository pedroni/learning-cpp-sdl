cmake_minimum_required(VERSION 3.10)
project(myprogram)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set homebrew paths
set(CMAKE_PREFIX_PATH "/opt/homebrew" ${CMAKE_PREFIX_PATH})

# Find SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Get all cpp files
file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(myprogram ${SOURCES})

# Link SDL2 with explicit paths
target_include_directories(myprogram PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_directories(myprogram PRIVATE ${SDL2_LIBRARY_DIRS})
target_link_libraries(myprogram ${SDL2_LIBRARIES})

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
