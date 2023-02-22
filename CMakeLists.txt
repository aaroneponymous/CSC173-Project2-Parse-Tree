cmake_minimum_required(VERSION 3.18)
project(Project_2_Parse_Tree C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(Project_2_Parse_Tree
        bits.c)
