#include "chunk.h"
#include "core.h"

void Chunk::generate(glm::vec2 chunk_position) {
    m_chunkPosition = chunk_position;

    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        m_tiles[i].id = GRASS_ID;
        m_tiles[i].variant = rand() % core->assetManager.getNumVariants(m_tiles[i].id);
    }
}

void Chunk::draw(SpriteBatch &sb) {
    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        u32 x = i % consts::CHUNK_SIZE;
        u32 y = i / consts::CHUNK_SIZE;

        sb.addSprite((glm::vec2(x, y) + m_chunkPosition * (f32)consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
                glm::vec2(consts::TILE_SIZE_METERS), core->assetManager.getTileUv(m_tiles[i]));
    }
}
