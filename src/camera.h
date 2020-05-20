#ifndef SPIRIT_CAMERA_H
#define SPIRIT_CAMERA_H

#include "types.h"
#include "constants.h"
#include "aabb.h"
#include <glm/glm.hpp>

struct Camera {
    glm::vec2 position = glm::vec2(0);
    f32 distance = 1.0f;
    f32 aspectRatio = 1.0f;

    /// Get the bottom left point and top right point in a vec4 in camera space
    [[nodiscard]] Aabb getCameraSpaceFrustumAabb() const {
        glm::vec2 halfDim = glm::vec2(
                consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT * 0.5f * distance * aspectRatio,
                consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT * 0.5f * distance
        );

        return Aabb(-halfDim, halfDim);
    }

    /// Get the bottom left point and top right point in a vec4 in world space
    [[nodiscard]] Aabb getWorldSpaceFrustumAabb() const {
        Aabb csAabb = getCameraSpaceFrustumAabb();
        return Aabb(position + csAabb.min, position + csAabb.max);
    }
};

#endif //SPIRIT_CAMERA_H
