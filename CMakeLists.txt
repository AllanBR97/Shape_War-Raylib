cmake_minimum_required(VERSION 3.26)
project(Shape_War C)

set(CMAKE_C_STANDARD 11)

add_executable(Shape_War main.c
        Player.c
        Player.h)
target_link_libraries(Shape_War raylib m)
