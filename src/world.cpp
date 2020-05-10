#include "world.h"
#include "core.h"

void World::init() {
    m_tileSpriteBatch.init();
    m_entitySpriteBatch.init();

    // Add chunks, temp
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
    m_tileSpriteBatch.clear();
    m_entitySpriteBatch.clear();

    for (auto &chunk : m_chunks) {
        chunk.draw(m_tileSpriteBatch, m_entitySpriteBatch);
    }

    m_tileSpriteBatch.draw();
    m_entitySpriteBatch.draw();
}
