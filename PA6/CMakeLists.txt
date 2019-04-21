cmake_minimum_required(VERSION 3.13)
project(PA6 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PA6
        pa6.c
        seqpair.c
        seqpair.h)
