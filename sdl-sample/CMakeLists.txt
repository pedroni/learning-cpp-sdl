cmake_minimum_required(VERSION 3.10)
project(myprogram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set homebrew paths
set(CMAKE_PREFIX_PATH "/opt/homebrew" ${CMAKE_PREFIX_PATH})

# Find SDL2_image (which includes SDL2 as dependency)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Get all cpp files
file(GLOB SOURCES "*.cpp")

# Create executable
add_executable(myprogram ${SOURCES})

# Link SDL2_image (includes SDL2 automatically)
target_include_directories(myprogram PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_directories(myprogram PRIVATE ${SDL2_IMAGE_LIBRARY_DIRS})
target_link_libraries(myprogram ${SDL2_IMAGE_LIBRARIES})

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
