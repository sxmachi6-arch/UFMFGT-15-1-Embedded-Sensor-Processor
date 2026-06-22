cmake_minimum_required(VERSION 3.21)
project(programmingFE C)

set(CMAKE_C_STANDARD 99)

add_executable(programmingFE main.c adc.h adc.c io.c io.h stats.h stats.c)
