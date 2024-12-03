cmake_minimum_required(VERSION 3.29.6)
project(AoC_2024 C)

set(CMAKE_C_STANDARD 11)

add_executable(AoC_2024 main.c
        common/common.c
        common/common.h
        Day_1/Day_1.c
        Day_1/Day_1.h
        Day_2/Day_2.c
        Day_2/Day_2.h
        Day_3/Day_3.c
        Day_3/Day_3.h)
