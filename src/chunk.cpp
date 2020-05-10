#include "chunk.h"
#include "core.h"

void Chunk::init() {
    m_tileSpriteBatch.init();
}

void Chunk::destroy() {
    m_tileSpriteBatch.destroy();
}

void Chunk::generate(glm::vec2 chunk_position) {
    m_chunkPosition = chunk_position;
    m_offset = m_chunkPosition * (f32) consts::CHUNK_SIZE * consts::TILE_SIZE_METERS;

    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        m_tiles[i].id = TILE_GRASS_ID;
        m_tiles[i].variant = rand() % core->assetManager.getNumVariants(m_tiles[i].id);
    }
}

void Chunk::populate(std::vector<Entity> &entities) {
    for (u32 i = 0; i < 6; ++i) {
        entities.emplace_back();
        entities.back().id = ENTITY_TEST_ID;
        entities.back().frame = rand() % core->assetManager.getNumFrames(entities.back().id);
        entities.back().position = glm::vec2(rand() / (f32) RAND_MAX, rand() / (f32) RAND_MAX)
                                   * (f32) (consts::CHUNK_SIZE - 1) + m_offset;
        entities.back().dimensions = glm::vec2(1);
    }
}

void Chunk::update() {
    // TODO
}

void Chunk::draw() {
    // Only re-batch sprites if tiles have changed
    if (m_isTileSpriteBatchDirty) {
        m_isTileSpriteBatchDirty = false;
        m_tileSpriteBatch.clear();

        // Add tile sprites
        for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
            u32 x = i % consts::CHUNK_SIZE;
            u32 y = i / consts::CHUNK_SIZE;

            // TODO: See if there is a better solution to separating lines than adding 0.001 to dimensions
            m_tileSpriteBatch.addSprite(glm::vec2(x, y) + m_offset,
                                        glm::vec2(consts::TILE_SIZE_METERS + 0.001),
                                        core->assetManager.getTileUv(m_tiles[i]));
        }
    }

    // Draw tiles
    m_tileSpriteBatch.draw();
}
