cmake_minimum_required(VERSION 3.26)
project(Shape_War C)

set(CMAKE_C_STANDARD 11)

add_executable(Shape_War main.c Game.c Meteor.c Player.c)
target_link_libraries(Shape_War raylib m)
