cmake_minimum_required(VERSION 3.30)
project(untitled C)

# Set C Standard
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(include)

# Source files
set(SOURCE_FILES
        src/buddy_system.c
        src/list.c
        src/virtual_mem.c
        src/main.c)

# Add the executable
add_executable(untitled ${SOURCE_FILES})