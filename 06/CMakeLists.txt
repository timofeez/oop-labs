cmake_minimum_required(VERSION 3.10)
project(patterns)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(06_npcs src/npc.cpp)
target_include_directories(06_npcs PRIVATE include)

add_library(06_dungeon src/dungeon.cpp)
target_include_directories(06_dungeon PRIVATE include)

add_executable(06 main.cpp)
target_include_directories(06 PRIVATE include)
target_link_libraries(06 PRIVATE 06_npcs 06_dungeon)
