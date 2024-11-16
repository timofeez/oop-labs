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

add_executable(lab3 main.cpp src/lab3.cpp)

target_include_directories(lab3 PRIVATE include)

enable_testing()

add_executable(test_lab3 test/test_3lab.cpp)

target_include_directories(test_lab3 PRIVATE include)

target_sources(test_lab3 PRIVATE src/lab3.cpp)

target_link_libraries(test_lab3 PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME FigureTests COMMAND test_lab3)
