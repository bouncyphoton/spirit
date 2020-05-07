cmake_minimum_required(VERSION 3.15)
project(spirit)

set(CMAKE_CXX_STANDARD 14)

add_executable(spirit src/main.cpp src/core.cpp src/core.h)
