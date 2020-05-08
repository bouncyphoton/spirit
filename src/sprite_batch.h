#ifndef SPIRIT_SPRITE_BATCH_H
#define SPIRIT_SPRITE_BATCH_H

#include "types.h"
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;
    glm::vec4 color;
};

class SpriteBatch {
public:
    SpriteBatch() = default;

    void init();

    void destroy();

    void addSprite(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 uv, glm::vec4 color = glm::vec4(1));

    void addSprite(glm::vec2 bottom_left, glm::vec2 dimensions, glm::vec4 uv, glm::vec4 color = glm::vec4(1));

    void draw();

    void clear();

private:
    u32 m_vao = 0;
    u32 m_vbo = 0;
    std::vector<Vertex> m_vertices;
};

#endif //SPIRIT_SPRITE_BATCH_H
