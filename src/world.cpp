#include "world.h"
#include "core.h"
#include <algorithm>

void World::init() {
    m_entitySpriteBatch.init();

    // Add chunks, temp
    for (s32 x = -2; x <= 2; ++x) {
        for (s32 y = -2; y <= 2; ++y) {
            m_chunks.emplace_back();
            m_chunks.back().init();
            m_chunks.back().generate(glm::vec2(x, y));
            m_chunks.back().populate(m_entities);
        }
    }
}

void World::destroy() {
    for (auto& chunk : m_chunks) {
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
    for (auto &chunk : m_chunks) {
        chunk.draw();
    }

    m_entitySpriteBatch.clear();

    std::sort(m_entities.begin(), m_entities.end(), [](Entity &a, Entity &b) {
        return a.position.y > b.position.y;
    });
    for (auto &entity : m_entities) {
        m_entitySpriteBatch.addSprite(entity.position, entity.dimensions,
                                      core->assetManager.getEntityUv(entity));
    }

    m_entitySpriteBatch.draw();
}
