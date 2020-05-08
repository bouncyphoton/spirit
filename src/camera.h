#ifndef SPIRIT_CAMERA_H
#define SPIRIT_CAMERA_H

#include "types.h"
#include <glm/glm.hpp>

struct Camera {
    glm::vec2 position = glm::vec2(0);
    f32 distance = 1.0f;
};

#endif //SPIRIT_CAMERA_H
