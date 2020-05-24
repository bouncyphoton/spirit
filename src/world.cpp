#include "world.h"
#include "core.h"
#include <algorithm>

void World::init() {
    m_entitySpriteBatch.init();

    s32 n = 5;

    // Add chunks, temp
    for (s32 x = -n; x <= n; ++x) {
        for (s32 y = -n; y <= n; ++y) {
            m_chunks.emplace_back();
            m_chunks.back().init();
            m_chunks.back().generate(glm::vec2(x, y));
            m_chunks.back().populate(m_entities);
        }
    }
}

void World::destroy() {
    for (auto &chunk : m_chunks) {
        chunk.destroy();
    }

    m_entitySpriteBatch.destroy();
}

void World::update() {
    for (auto &chunk : m_chunks) {
        chunk.update();
    }
}

void World::draw() {
    Aabb frustumAabb = core->camera.getWorldSpaceFrustumAabb();

    // Draw chunks in view
    for (auto &chunk : m_chunks) {
        if (frustumAabb.overlap(chunk.getAabb())) {
            chunk.draw();
        }
    }

    m_entitySpriteBatch.clear();

    // Sort entities for correct overlaps
    std::sort(m_entities.begin(), m_entities.end(), [](Entity &a, Entity &b) {
        return a.position.y > b.position.y;
    });
    for (auto &entity : m_entities) {
        m_entitySpriteBatch.addSprite(entity.position, entity.dimensions,
                                      core->assetManager.getSprite(entity.spriteName));
    }

    // Draw entities
    m_entitySpriteBatch.draw();
}
