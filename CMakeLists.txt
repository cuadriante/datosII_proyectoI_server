cmake_minimum_required(VERSION 3.20)
project(datosII_proyectoI_server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(datosII_proyectoI_server main.cpp ServerSocket.cpp ServerSocket.h)
