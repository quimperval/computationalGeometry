cmake_minimum_required(VERSION 3.22.1)
project(LineSegmentIntersections)


#Set the path to GTEST manually
set(GTEST_INCLUDE_DIR $ENV{HOME}/Apps/googletest-1.14.0/googletest/include)
set(GMOCK_INCLUDE_DIR $ENV{HOME}/Apps/googletest-1.14.0/googlemock/include)
set(GTEST_LIBRARY $ENV{HOME}/Apps/googletest-1.14.0/build/lib/libgtest.a)
set(GMOCK_LIBRARY $ENV{HOME}/Apps/googletest-1.14.0/build/lib/libgmock.a)
set(POINT_INCLUDE ../convexHull     )
set(AVL_INCLUDE ../AVLTree     )
set(BST_INCLUDE ../BST)
# Include directories
include_directories(
    include 
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
    ${POINT_INCLUDE}
    ${AVL_INCLUDE}
    ${BST_INCLUDE}
)

# Add test executable
add_executable(runTests LSITesting.cpp)
target_link_libraries(runTests ${GTEST_LIBRARY} pthread)
# Add compiler options (debugging symbols)
target_compile_options(runTests PRIVATE -g)