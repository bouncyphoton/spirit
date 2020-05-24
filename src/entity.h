#ifndef SPIRIT_ENTITY_H
#define SPIRIT_ENTITY_H

#include <glm/glm.hpp>
#include <string>

struct Entity {
    std::string spriteName;
    glm::vec2 position;
    glm::vec2 dimensions;
};

#endif //SPIRIT_ENTITY_H
