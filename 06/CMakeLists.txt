cmake_minimum_required(VERSION 3.10)
project(patterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем библиотеку NPCs
add_library(06_npcs src/npc.cpp)
target_include_directories(06_npcs PRIVATE include)

# Добавляем библиотеку Dungeon
add_library(06_dungeon src/dungeon.cpp)
target_include_directories(06_dungeon PRIVATE include)

# Добавляем основной исполнимый файл
add_executable(06 main.cpp)
target_include_directories(06 PRIVATE include)
target_link_libraries(06 PRIVATE 06_npcs 06_dungeon)

# Включаем поддержку тестов
enable_testing()

# Добавляем тесты
add_executable(06_tests test/test_6lab.cpp)
target_include_directories(06_tests PRIVATE include)

# Указываем правильные библиотеки для тестов
target_link_libraries(06_tests PRIVATE 06_npcs 06_dungeon GTest::gtest GTest::gtest_main)

# Добавляем тесты в CMake
add_test(NAME test_06 COMMAND 06_tests)
