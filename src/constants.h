#ifndef SPIRIT_CONSTANTS_H
#define SPIRIT_CONSTANTS_H

#include "types.h"

namespace consts {
    static constexpr u32 OPENGL_VERSION_MAJOR = 3;
    static constexpr u32 OPENGL_VERSION_MINOR = 3;

    static constexpr f32 TARGET_HERTZ = 60.0f;

    // How many in-game meters tall the 2D camera "frustum" is at default zoom
    static constexpr f32 DEFAULT_CAMERA_FRUSTUM_HEIGHT = 10.0f;

    // Maximum "distance" camera can be
    static constexpr f32 CAMERA_MAX_DISTANCE = 4.0f;

    // Minimum "distance" camera can be
    static constexpr f32 CAMERA_MIN_DISTANCE = 0.5f;

    // Number of tiles wide a chunk is
    static constexpr u32 CHUNK_SIZE = 8;

    // Size of a tile in meters
    static constexpr f32 TILE_SIZE_METERS = 1.0f;

    // Texture atlas extension
    static constexpr const char *TEXTURE_EXTENSION = ".png";

    static constexpr const char *MISSING_TEXTURE_NAME = "*missing";

    static constexpr const char *WHITE_TEXTURE_NAME = "*white";
}

#endif //SPIRIT_CONSTANTS_H
