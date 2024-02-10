cmake_minimum_required(VERSION 3.10)
project(Facial-Recognition)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(src/utils)

# Add main executable
add_executable(main src/main.cpp src/utils/matrix.h)

# Add test executable
add_executable(test src/tests/test_matrix.cpp src/utils/matrix.h)
