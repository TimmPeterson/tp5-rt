cmake_minimum_required(VERSION 4.0)
project(TestSDL2)

# Make additinal inner directory build/bin/ for executable and libs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin)

# Generate compile_command.json file for clangd
set(DCMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 lib
include_directories(${SDL2_INCLUDE_DIRS})

# Collect certain blocks of source files
file(GLOB_RECURSE SRC_RT "src/rt/*.cpp")
file(GLOB_RECURSE SRC_MTH "src/mth/*.cpp")
file(GLOB_RECURSE SRC_WIN "src/win/*.cpp")
file(GLOB_RECURSE SRC_FRAME "src/frame/*.cpp")
set(SRC_MAIN "src/main.cpp")

# Create executable
add_executable(app ${SRC_MAIN} ${SRC_FRAME} ${SRC_WIN} ${SRC_MTH} ${SRC_RT})

# Link SDL2 to the program 
target_link_libraries(app ${SDL2_LIBRARIES})

# Add extra include dirs ("." and "./src")
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR})