cmake_minimum_required(VERSION 3.10)
project(oop-labs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(npcs
    src/npc.cpp
    src/visitor.cpp
    src/factory.cpp
    src/observer.cpp
    src/utils.cpp
)
target_include_directories(npcs PUBLIC include)

add_library(dungeon
    src/dungeon.cpp
)
target_include_directories(dungeon PUBLIC include)
target_link_libraries(dungeon PUBLIC npcs)

add_library(managers
    src/movement_manager.cpp
    src/battle_manager.cpp
)
target_include_directories(managers PUBLIC include)
target_link_libraries(managers PUBLIC dungeon npcs)

add_executable(07 main.cpp)
target_include_directories(07 PUBLIC include)
target_link_libraries(07 PUBLIC dungeon npcs managers)
