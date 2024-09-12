cmake_minimum_required(VERSION 3.24)
project(GameOfLife_preproject C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED SDL2)
include_directories(GameOfLife ${SDL2_INCLUDE_DIRS})


add_executable(GameOfLife main.c make_matrix.c make_matrix.h)
target_link_libraries(GameOfLife ${SDL2_LIBRARIES})