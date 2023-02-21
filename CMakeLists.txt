cmake_minimum_required(VERSION 3.22)
project(Tarea1_Grupo1)

set(CMAKE_CXX_STANDARD 14)

main: main.cpp
cpp -I boost_1_81_0 main.cpp -o main

add_executable(Tarea1_Grupo1 main.cpp Functions.cpp Functions.h)
