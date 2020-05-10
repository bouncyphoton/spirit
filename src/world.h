#ifndef SPIRIT_WORLD_H
#define SPIRIT_WORLD_H

#include "sprite_batch.h"
#include "chunk.h"
#include <vector>

class World {
public:
    void init();

    void destroy();

    void update();

    void draw();

private:
    SpriteBatch m_tileSpriteBatch;
    SpriteBatch m_entitySpriteBatch;

    std::vector<Chunk> m_chunks;
};

#endif //SPIRIT_WORLD_H
