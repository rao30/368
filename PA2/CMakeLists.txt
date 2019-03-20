cmake_minimum_required(VERSION 3.13)
project(PA2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PA2
        pa2.c
        sequence.c
        sequence.h
        shell_array.c
        shell_array.h
        shell_list.c
        shell_list.h)
