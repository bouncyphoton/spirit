#ifndef SPIRIT_ENTITY_H
#define SPIRIT_ENTITY_H

#include "types.h"
#include <glm/glm.hpp>

struct Entity {
    u32 spriteId;
    u32 spriteVariant;
    glm::vec2 position;
    glm::vec2 dimensions;
};

#endif //SPIRIT_ENTITY_H
