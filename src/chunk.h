#ifndef SPIRIT_CHUNK_H
#define SPIRIT_CHUNK_H

#include "tile.h"
#include "constants.h"
#include "sprite_batch.h"
#include "entity.h"
#include <glm/glm.hpp>
#include <vector>

class Chunk {
public:
    Chunk() = default;

    void init();

    void destroy();

    /// Generate tiles based off chunk position
    void generate(glm::vec2 chunk_position);

    /// Populate a list of entities based off chunk tiles
    void populate(std::vector<Entity> &entities);

    /// Load chunk from file
    // ...

    void update();

    void draw();

private:
    glm::vec2 m_chunkPosition = glm::vec2(0);
    glm::vec2 m_offset = glm::vec2(0);
    Tile m_tiles[consts::CHUNK_SIZE * consts::CHUNK_SIZE] = {};

    SpriteBatch m_tileSpriteBatch;

    bool m_isTileSpriteBatchDirty = true;
};

#endif //SPIRIT_CHUNK_H
