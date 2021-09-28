cmake_minimum_required(VERSION 3.20)
project(datosII_proyectoI_server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(datosII_proyectoI_server Sources/main.cpp Sources/Socket.cpp Headers/Socket.h Sources/Breakout/Block.cpp Headers/Breakout/Block.h Sources/ServerListener.cpp Headers/ServerListener.h Sources/Command.cpp Headers/Command.h Sources/Breakout/GameInfo.cpp Headers/Breakout/GameInfo.h Sources/Breakout/Ball.cpp Headers/Breakout/Ball.h Sources/PlayerInfo.cpp Headers/PlayerInfo.h Sources/Breakout/PlayerBar.cpp Headers/Breakout/PlayerBar.h)
