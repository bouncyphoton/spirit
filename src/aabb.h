#ifndef SPIRIT_AABB_H
#define SPIRIT_AABB_H

#include "types.h"
#include <glm/glm.hpp>

/// Axis Aligned Bounding Box
class Aabb {
public:
    Aabb(glm::vec2 min, glm::vec2 max) : min(min), max(max) {}

    glm::vec2 min;
    glm::vec2 max;

    [[nodiscard]] bool overlap(const Aabb &o) {
        return (min.x < o.max.x && max.x > o.min.x && min.y < o.max.y && max.y > o.min.y);
    }
};

#endif //SPIRIT_AABB_H
