#include "sprite_batch.h"
#include "core.h"
#include <GL/gl3w.h>

void SpriteBatch::init() {
    glGenVertexArrays(1, &m_vao);
    if (m_vao == 0) {
        core->logFatal("Failed to generate vertex array for sprite batch");
    }
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    if (m_vbo == 0) {
        core->logFatal("Failed to generate vertex buffer object for sprite batch");
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, colorUv));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normalUv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));

    glBindVertexArray(0);
}

void SpriteBatch::destroy() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void SpriteBatch::addSprite(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3,
                            const Sprite &sprite, glm::vec4 tint) {
    glm::vec4 cUv = sprite.colorUv;
    glm::vec4 nUv = sprite.normalUv;
    Vertex v0{p0, glm::vec2(cUv.x, cUv.y), glm::vec2(nUv.x, nUv.y), tint};
    Vertex v1{p1, glm::vec2(cUv.z, cUv.y), glm::vec2(nUv.z, nUv.y), tint};
    Vertex v2{p2, glm::vec2(cUv.z, cUv.w), glm::vec2(nUv.z, nUv.w), tint};
    Vertex v3{p3, glm::vec2(cUv.x, cUv.w), glm::vec2(nUv.x, nUv.w), tint};

    // TODO: to optimize performance, move away from std::vector

    m_vertices.emplace_back(v0);
    m_vertices.emplace_back(v1);
    m_vertices.emplace_back(v2);

    m_vertices.emplace_back(v0);
    m_vertices.emplace_back(v2);
    m_vertices.emplace_back(v3);
}

void SpriteBatch::addSprite(glm::vec2 bottom_left, glm::vec2 dimensions, const Sprite &sprite, glm::vec4 tint) {
    addSprite(bottom_left,
              bottom_left + glm::vec2(dimensions.x, 0),
              bottom_left + dimensions,
              bottom_left + glm::vec2(0, dimensions.y),
              sprite, tint);
}

void SpriteBatch::draw() {
    // TODO: check performance
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}

void SpriteBatch::clear() {
    m_vertices.clear();
}
