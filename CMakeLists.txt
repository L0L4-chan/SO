cmake_minimum_required(VERSION 3.24)
project(p0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(p0
        dynamic_list.c
        dynamic_list.h
        P0.c
        P0.h
        types.h
        ToTest.c)