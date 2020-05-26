cmake_minimum_required(VERSION 3.15)
project(spirit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)

add_executable(spirit third-party/gl3w/gl3w.c src/main.cpp src/core.cpp src/core.h src/platform.cpp src/platform.h src/constants.h src/config.h src/types.h src/shader.cpp src/shader.h src/shader_source.h src/sprite_batch.cpp src/sprite_batch.h src/camera.h src/texture_atlas.cpp src/texture_atlas.h src/world.cpp src/world.h src/chunk.cpp src/chunk.h src/asset_manager.cpp src/asset_manager.h src/aabb.h src/sprite.h src/entity.h src/tile.h)
target_link_libraries(spirit ${SDL2_LIBRARY})
target_include_directories(spirit PUBLIC ${SDL2_INCLUDE_DIR} third-party/gl3w/include third-party/glm third-party/stb)
