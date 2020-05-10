#include "world.h"
#include "core.h"
#include "constants.h"

void World::init() {
    m_tileSpriteBatch.init();
    m_entitySpriteBatch.init();

    // Add one chunk
    for (s32 x = -2; x <= 2; ++x) {
        for (s32 y = -2; y <= 2; ++y) {
            m_chunks.emplace_back();
            m_chunks.back().generate(glm::vec2(x, y));
        }
    }
}

void World::destroy() {
    m_entitySpriteBatch.destroy();
    m_tileSpriteBatch.destroy();
}

void World::update() {
    // TODO
}

void World::draw() {
    // Draw world tiles
    {
        m_tileSpriteBatch.clear();

        for (auto& chunk : m_chunks) {
            chunk.draw(m_tileSpriteBatch);
        }

        m_tileSpriteBatch.draw();
    }

    // TODO: figure out entity uv look up when entities are implemented
    // Draw entities
/*    {
        m_entitySpriteBatch.clear();

        constexpr u32 numEntityTextures = 3;
        static glm::vec4 entityUvs[numEntityTextures] = {
                core->textureAtlas.getUv("entity0.png"),
                core->textureAtlas.getUv("entity1.png"),
                core->textureAtlas.getUv("entity2.png"),
        };

        for (u32 i = 0; i < 5; ++i) {
            f32 x = (f32) rand() / (f32) RAND_MAX * (consts::CHUNK_SIZE - 1);
            f32 y = (f32) rand() / (f32) RAND_MAX * (consts::CHUNK_SIZE - 1);

            m_entitySpriteBatch.addSprite(glm::vec2(x, y) * consts::TILE_SIZE_METERS,
                                          glm::vec2(consts::TILE_SIZE_METERS),
                                          entityUvs[rand() % numEntityTextures]);
        }

        m_entitySpriteBatch.draw();
    }*/
}
