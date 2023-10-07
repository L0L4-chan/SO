cmake_minimum_required(VERSION 3.24)
project(p1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(p1
        linkedList.c
        linkedList.h
        p1.c
        p1.h
        dynamic_list.h
        p0.c
        p0.h
        types.h
        )