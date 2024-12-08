cmake_minimum_required(VERSION 3.10)
project(6_thread_version)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем вывод отладочной информации
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Добавляем библиотеку NPCs
add_library(07_npcs
    src/npc.cpp
    src/visitor.cpp
    src/factory.cpp
    src/observer.cpp
)
target_include_directories(07_npcs PRIVATE include)

# Добавляем библиотеку Dungeon
add_library(07_dungeon
    src/dungeon.cpp
)
target_include_directories(07_dungeon PRIVATE include)

# Добавляем основной исполнимый файл
add_executable(07 main.cpp)
target_include_directories(07 PRIVATE include)
target_link_libraries(07 PRIVATE 07_dungeon 07_npcs)

