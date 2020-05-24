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

    // Generate tiles
    for (u32 i = 0; i < consts::CHUNK_SIZE * consts::CHUNK_SIZE; ++i) {
        m_tiles[i].spriteName = "grass0";
    }
}

void Chunk::populate(std::vector<Entity> &entities) {
    static const char *tileChoices[] = {"sphere", "rock0", "flower0"};

    for (u32 x = 0; x < consts::CHUNK_SIZE; ++x) {
        for (u32 y = 0; y < consts::CHUNK_SIZE; ++y) {
            if (rand() % 20 == 0) {
                entities.emplace_back();
                entities.back().spriteName = tileChoices[rand() % 3];
                entities.back().position = glm::vec2(x, y) + m_offset;
                entities.back().dimensions = glm::vec2(consts::TILE_SIZE_METERS);
            }
        }
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

            m_tileSpriteBatch.addSprite(glm::vec2(x, y) * consts::TILE_SIZE_METERS + m_offset,
                                        glm::vec2(consts::TILE_SIZE_METERS),
                                        core->assetManager.getSprite(m_tiles[i].spriteName));
        }
    }

    // Draw tiles
    m_tileSpriteBatch.draw();

    // Draw outlines
//    core->debugBatch.addSprite(m_chunkPosition * glm::vec2(consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
//                               glm::vec2(consts::CHUNK_SIZE, 1.0 / 16.0f) * consts::TILE_SIZE_METERS,
//                               core->assetManager.getWhiteUv(),
//                               glm::vec4(1, 0, 0, 1));
//
//    core->debugBatch.addSprite(m_chunkPosition * glm::vec2(consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
//                               glm::vec2(1.0 / 16.0f, consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
//                               core->assetManager.getWhiteUv(),
//                               glm::vec4(1, 0, 0, 1));
}
