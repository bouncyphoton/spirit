#ifndef SPIRIT_ENTITY_H
#define SPIRIT_ENTITY_H

#include "types.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

enum EntityIdEnum : u32 {
    ENTITY_TEST_ID,
    ENTITY_FLOWER_ID,
    ENTITY_ROCK_ID,
    NUM_ENTITIES
};

struct EntityInfo {
    EntityIdEnum id;
    u32 numFrames;
    std::string textureBaseName;
};

struct Entity {
    EntityIdEnum id;
    u8 frame;
    glm::vec2 position;
    glm::vec2 dimensions;
};

extern std::vector<EntityInfo> entityInfoList;

#endif //SPIRIT_ENTITY_H
