#ifndef SPIRIT_WORLD_H
#define SPIRIT_WORLD_H

#include "sprite_batch.h"
#include "chunk.h"
#include "entity.h"
#include <vector>

class World {
public:
    void init();

    void destroy();

    void update();

    void draw();

private:
    std::vector<Chunk> m_chunks;
    std::vector<Entity> m_entities;

    SpriteBatch m_entitySpriteBatch;
};

#endif //SPIRIT_WORLD_H
