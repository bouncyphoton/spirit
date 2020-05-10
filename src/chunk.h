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

    void generate(glm::vec2 chunk_position);

    void draw(SpriteBatch &tile_sb, SpriteBatch &entity_sb);
private:
    glm::vec2 m_chunkPosition = glm::vec2(0);
    Tile m_tiles[consts::CHUNK_SIZE * consts::CHUNK_SIZE] = {};
    std::vector<Entity> m_entities = {};
};

#endif //SPIRIT_CHUNK_H
