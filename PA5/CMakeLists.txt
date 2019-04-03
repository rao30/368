cmake_minimum_required(VERSION 3.13)
project(PA5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PA5
        pa5.c
        sorting.c
        sorting.h)
