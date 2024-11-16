cmake_minimum_required(VERSION 3.20)

project(QueueWithMemoryResource)

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

add_executable(queue_app main.cpp)
target_include_directories(queue_app PRIVATE include)
target_sources(queue_app PRIVATE src/QueueMemoryResource.cpp)

enable_testing()

add_executable(test_queue test/test_queue.cpp)
target_include_directories(test_queue PRIVATE include)
target_sources(test_queue PRIVATE src/QueueMemoryResource.cpp)
target_link_libraries(test_queue PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME QueueTests COMMAND test_queue)

add_executable(test_queue_memory_resource test/test_queue_memory_resource.cpp)
target_include_directories(test_queue_memory_resource PRIVATE include)
target_sources(test_queue_memory_resource PRIVATE src/QueueMemoryResource.cpp)
target_link_libraries(test_queue_memory_resource PRIVATE GTest::gtest GTest::gtest_main)
add_test(NAME QueueMemoryResourceTests COMMAND test_queue_memory_resource)
