#include "core.h"
#include "shader_source.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl3w.h>
#include <cstdlib>
#include <iostream>

static Core core_local;
Core *core = &core_local;

void Core::run() {
    init();

    logInfo("Initialized successfully");

    // Main loop runs until quit() is called
    while (true) {
        m_platform.update();

        update();

        render();

        m_platform.swapBuffers();
    }
}

void Core::quit() {
    cleanup();
    exit(0);
}

void Core::logFatal(const std::string &msg) {
    std::cerr << "[fatal] " << msg << std::endl;
    cleanup();
    exit(1);
}

void Core::logInfo(const std::string &msg) {
    std::cout << "[info] " << msg << std::endl;
}

void Core::init() {
    // TODO: load this config from somewhere
    config.frameWidth = 800;
    config.frameHeight = 600;

    m_platform.init();
    m_spriteShader.init(sprite_vertex_src, sprite_fragment_src);
    m_spriteBatch.init();
}

void Core::cleanup() {
    m_spriteBatch.destroy();
    m_spriteShader.destroy();
    m_platform.destroy();
}

void Core::update() {
    // TODO
    m_spriteBatch.clear();

    int w = 75;
    int h = 75;
    constexpr int n = 7;

    glm::vec4 colors[n] = {
            glm::vec4(1.0, 0.0, 0.0, 1),
            glm::vec4(1, 0.5, 0, 1),
            glm::vec4(1, 1, 0, 1),
            glm::vec4(0, 1, 0, 1),
            glm::vec4(0, 0, 1, 1),
            glm::vec4(0.25, 0, 1, 1),
            glm::vec4(0.3, 0, 0.5, 1),
    };

    glm::vec2 bl = glm::vec2(config.frameWidth / 2.0f - w * n / 2.0f, config.frameHeight / 2.0f - h / 2.0f);
    for (int i = 0; i < n; ++i) {
        m_spriteBatch.addSprite(bl + glm::vec2(w * i, 0), glm::vec2(w, h), colors[i]);
    }
}

void Core::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_spriteShader.bind();

    // Set matrix
    glm::mat4 projection = glm::ortho<float>(0, config.frameWidth, 0, config.frameHeight);
    m_spriteShader.setMat4("uProjectionMatrix", projection);

    // Texture atlas is bound to texture unit 0
    m_spriteShader.setInt("uAtlas", 0);

    // Draw sprites
    m_spriteBatch.draw();

    // TODO: Draw calls for sprites
}
