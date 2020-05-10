#ifndef SPIRIT_CHUNK_H
#define SPIRIT_CHUNK_H

#include "tile.h"
#include "constants.h"
#include "sprite_batch.h"
#include <glm/glm.hpp>

class Chunk {
public:
    Chunk() = default;

    void generate(glm::vec2 chunk_position);

    void draw(SpriteBatch &sb);
private:
    glm::vec2 m_chunkPosition;
    Tile m_tiles[consts::CHUNK_SIZE * consts::CHUNK_SIZE] = {};
};

#endif //SPIRIT_CHUNK_H
