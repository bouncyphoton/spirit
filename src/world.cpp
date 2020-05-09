#include "world.h"
#include "core.h"

void World::init() {
    m_tileSpriteBatch.init();
    m_entitySpriteBatch.init();
}

void World::destroy() {
    m_entitySpriteBatch.destroy();
    m_tileSpriteBatch.destroy();
}

void World::draw() {
    // temp
    constexpr u32 chunkSize = 8;

    // Draw world tiles
    {
        m_tileSpriteBatch.clear();

        constexpr u32 numGrassTextures = 3;
        static glm::vec4 grassUvs[numGrassTextures] = {
                core->textureAtlas.getUv("floor_1.png"),
                core->textureAtlas.getUv("floor_2.png"),
                core->textureAtlas.getUv("floor_3.png"),
        };

        // TODO: separate drawing into chunks
        for (u32 i = 0; i < chunkSize; ++i) {
            for (u32 j = 0; j < chunkSize; ++j) {
                m_tileSpriteBatch.addSprite(glm::vec2(i, j), glm::vec2(1), grassUvs[rand() % numGrassTextures]);
            }
        }

        m_tileSpriteBatch.draw();
    }

    // Draw entities
    {
        m_entitySpriteBatch.clear();

        constexpr u32 numEntityTextures = 3;
        static glm::vec4 entityUvs[numEntityTextures] = {
                core->textureAtlas.getUv("goblin_idle_anim_f0.png"),
                core->textureAtlas.getUv("imp_idle_anim_f0.png"),
                core->textureAtlas.getUv("tiny_zombie_idle_anim_f0.png"),
        };

        for (u32 i = 0; i < 5; ++i) {
            f32 x = (f32)rand() / (f32)RAND_MAX * (chunkSize - 1);
            f32 y = (f32)rand() / (f32)RAND_MAX * (chunkSize - 1);

            m_entitySpriteBatch.addSprite(glm::vec2(x, y), glm::vec2(1), entityUvs[rand() % numEntityTextures]);
        }

        m_entitySpriteBatch.draw();
    }
}
