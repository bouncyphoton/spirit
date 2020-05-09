#ifndef SPIRIT_WORLD_H
#define SPIRIT_WORLD_H

#include "sprite_batch.h"

class World {
public:
    void init();

    void destroy();

    void draw();

private:
    SpriteBatch m_tileSpriteBatch;
    SpriteBatch m_entitySpriteBatch;
};

#endif //SPIRIT_WORLD_H
