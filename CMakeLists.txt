cmake_minimum_required(VERSION 3.15)
project(spirit)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

add_executable(spirit third-party/gl3w/gl3w.c src/main.cpp src/core.cpp src/core.h src/platform.cpp src/platform.h src/defines.h src/config.h src/types.h)
target_link_libraries(spirit ${SDL2_LIBRARY})
target_include_directories(spirit PUBLIC ${SDL2_INCLUDE_DIR} third-party/gl3w/include)
