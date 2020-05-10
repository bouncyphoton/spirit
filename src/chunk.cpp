#include "chunk.h"
#include "core.h"
#include <algorithm>

void Chunk::generate(glm::vec2 chunk_position) {
    m_chunkPosition = chunk_position;

    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        m_tiles[i].id = TILE_GRASS_ID;
        m_tiles[i].variant = rand() % core->assetManager.getNumVariants(m_tiles[i].id);
    }

    for (u32 i = 0; i < 6; ++i) {
        m_entities.emplace_back();
        m_entities.back().id = ENTITY_TEST_ID;
        m_entities.back().frame = rand() % core->assetManager.getNumFrames(m_entities.back().id);
        m_entities.back().position = glm::vec2(rand() / (f32) RAND_MAX, rand() / (f32) RAND_MAX)
                                     * (f32) consts::CHUNK_SIZE;
        m_entities.back().dimensions = glm::vec2(1);
    }
}

void Chunk::draw(SpriteBatch &tile_sb, SpriteBatch &entity_sb) {
    glm::vec2 offset = m_chunkPosition * (f32) consts::CHUNK_SIZE * consts::TILE_SIZE_METERS;

    // Add tile sprites
    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        u32 x = i % consts::CHUNK_SIZE;
        u32 y = i / consts::CHUNK_SIZE;

        tile_sb.addSprite(glm::vec2(x, y) + offset,
                          glm::vec2(consts::TILE_SIZE_METERS), core->assetManager.getTileUv(m_tiles[i]));
    }

    // Add entity sprites, from back to front
    std::sort(m_entities.begin(), m_entities.end(), [](Entity &a, Entity &b) {
        return a.position.y > b.position.y;
    });
    for (auto &entity : m_entities) {
        entity_sb.addSprite(entity.position + offset, entity.dimensions, core->assetManager.getEntityUv(entity));
    }
}
