cmake_minimum_required(VERSION 3.16)
project(5042)

set(CMAKE_CXX_STANDARD 14)

add_executable(5042 main.cpp connection.cpp connection.h connection.h game.h game.cpp server.h server.cpp)