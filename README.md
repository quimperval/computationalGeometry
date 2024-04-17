 # Computational geometry

 ## Objective 

 This repository is to have some samples of computational geometry algorithms as a reference. 

 ## How to run the samples?

 In each folder exists a file buildAndTest.sh, it contains the below lines: 

    mkdir -p build &&
    cd build && 
    cmake .. &&
    cmake --build . &&
    ./runTests

This file uses the CMakeLists.txt file in the folder. 

For example, be in the convexHull folder you only have to type the below: 

    .../convexHull$ bash buildAndTest.sh

And you'll get the project compiled and the tests executed. 

In case you have any error, use the script: 

    .../convexHull$ bash buildAndDebug.sh

It will use the gdb and to run the tests you have to type: 

    (gdb) run <PRESS ENTER>

it will run the project and show you the failure. 

If you need the "stacktrace of the failure" type: 

    (gdb) backtrace

And you'll get something like: 

    #0  0x0000555555566d1e in std::vector<Point, std::allocator<Point> >::size (this=0x0) at /usr/include/c++/11/bits/stl_vector.h:919
    #1  0x0000555555561eef in ConvexHullTesting_getConvexHullA_Test::TestBody (this=0x5555556127d0)
    at /home/quimperval/computationalGeometry/convexHull/ConvexHullTest.cpp:41
    #2  0x00005555555b2ec3 in void testing::internal::HandleSehExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) ()
    #3  0x00005555555ab09f in void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void (testing::Test::*)(), char const*) ()
    #4  0x00005555555845f0 in testing::Test::Run() ()
    #5  0x000055555558510b in testing::TestInfo::Run() ()
    #6  0x0000555555585b11 in testing::TestSuite::Run() ()
    #7  0x0000555555596038 in testing::internal::UnitTestImpl::RunAllTests() ()
    #8  0x00005555555b4018 in bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) ()
    #9  0x00005555555ac3c5 in bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*) ()
    #10 0x0000555555594639 in testing::UnitTest::Run() ()
    #11 0x00005555555650ce in RUN_ALL_TESTS () at /home/quimperval/Apps/googletest-1.14.0/googletest/include/gtest/gtest.h:2317
    #12 0x00005555555639ea in main (argc=1, argv=0x7fffffffe028) at /home/quimperval/computationalGeometry/convexHull/ConvexHullTest.cpp:96
    (gdb) exit
