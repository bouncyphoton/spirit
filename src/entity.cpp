#include "entity.h"

// { u32 id, u32 numFrames, str textureBaseName }
// { 0, 2, "foo" } will associate the id 0 with the textures "foo0.png" and "foo1.png"
// numFrames should be at least 1
std::vector<EntityInfo> entityInfoList = {
//        {ENTITY_TEST_ID, 3, "entity"},
        {ENTITY_FLOWER_ID, 1, "flower"},
        {ENTITY_ROCK_ID, 1, "rock"},
};
