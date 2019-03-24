cmake_minimum_required(VERSION 3.13)
project(PA4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PA4
        main.c
        tree.c
        tree.h)
