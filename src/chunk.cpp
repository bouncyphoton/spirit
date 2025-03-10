#include "chunk.h"
#include "sprite.h"
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
        m_tiles[i].spriteId = SPRITE_GRASS;
        m_tiles[i].spriteVariant = rand() % core->assetManager.getNumVariants(m_tiles[i].spriteId);
    }
}

void Chunk::populate(std::vector<Entity> &entities) {
    for (u32 x = 0; x < consts::CHUNK_SIZE; ++x) {
        for (u32 y = 0; y < consts::CHUNK_SIZE; ++y) {
            if (rand() % 10 == 0) {
                entities.emplace_back();
                entities.back().spriteId = rand() % 2 == 0 ? SPRITE_ROCK : SPRITE_FLOWER;
                entities.back().spriteVariant = rand() % core->assetManager.getNumVariants(entities.back().spriteId);
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
                                        core->assetManager.getUv(m_tiles[i].spriteId, m_tiles[i].spriteVariant));
        }
    }

    // Draw tiles
    m_tileSpriteBatch.draw();

    // Draw outlines
    core->debugBatch.addSprite(m_chunkPosition * glm::vec2(consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
                               glm::vec2(consts::CHUNK_SIZE, 1.0 / 16.0f) * consts::TILE_SIZE_METERS,
                               core->assetManager.getUv(SPRITE_WHITE),
                               glm::vec4(1, 0, 0, 1));

    core->debugBatch.addSprite(m_chunkPosition * glm::vec2(consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
                               glm::vec2(1.0 / 16.0f, consts::CHUNK_SIZE) * consts::TILE_SIZE_METERS,
                               core->assetManager.getUv(SPRITE_WHITE),
                               glm::vec4(1, 0, 0, 1));
}
