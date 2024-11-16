cmake_minimum_required(VERSION 3.20)

project(GeometryFigures)

set(CMAKE_CXX_STANDARD 20)
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

add_executable(geometry_figures main.cpp)
target_include_directories(geometry_figures PRIVATE include)

enable_testing()

add_executable(test_geometry_figures test/test_4lab.cpp)
target_include_directories(test_geometry_figures PRIVATE include)
target_link_libraries(test_geometry_figures PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME GeometryFiguresTests COMMAND test_geometry_figures)
