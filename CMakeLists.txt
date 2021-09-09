cmake_minimum_required(VERSION 3.20)
project(datosII_proyectoI_server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(datosII_proyectoI_server Sources/main.cpp Sources/ServerSocket.cpp Headers/ServerSocket.h Sources/Protocol.cpp Headers/Protocol.h Sources/Breakout/BlockList.cpp Headers/Breakout/BlockList.h Sources/Breakout/PlayerList.cpp Headers/Breakout/PlayerList.h)
