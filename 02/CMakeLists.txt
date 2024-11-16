cmake_minimum_required(VERSION 3.20)

project(oop-labs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lab2 main.cpp src/three.cpp)

target_include_directories(lab2 PRIVATE include)

enable_testing()

add_executable(test_lab2 test/test_2lab.cpp src/three.cpp)

target_include_directories(test_lab2 PRIVATE include)

target_link_libraries(test_lab2 PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME ThreeTests COMMAND test_lab2)
