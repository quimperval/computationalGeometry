cmake_minimum_required(VERSION 3.22.1)
project(ConvexHullTest)


#Set the path to GTEST manually
set(GTEST_INCLUDE_DIR $ENV{HOME}/Apps/googletest-1.14.0/googletest/include)
set(GMOCK_INCLUDE_DIR $ENV{HOME}/Apps/googletest-1.14.0/googlemock/include)
set(GTEST_LIBRARY $ENV{HOME}/Apps/googletest-1.14.0/build/lib/libgtest.a)
set(GMOCK_LIBRARY $ENV{HOME}/Apps/googletest-1.14.0/build/lib/libgmock.a)

# Include directories
include_directories(
    include 
    ${GTEST_INCLUDE_DIR}
    ${GMOCK_INCLUDE_DIR}
)

# Add test executable
add_executable(runTests ConvexHullTest.cpp)
target_link_libraries(runTests ${GTEST_LIBRARY} pthread)