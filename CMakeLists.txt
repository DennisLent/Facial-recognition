cmake_minimum_required(VERSION 3.10)
project(Facial-Recognition)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(src/utils)

#Add packages
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add main executable
add_executable(main 
src/main.cpp
src/utils/matrix.h
src/utils/image.h
src/utils/pca.h)

#link
target_link_libraries( main ${OpenCV_LIBS} )

# Add test executable
add_executable(test 
src/tests/main_tests.cpp
src/tests/test_matrix.h
src/tests/test_image.h 
src/utils/matrix.h
src/utils/image.h)

#link
target_link_libraries( test ${OpenCV_LIBS} )
