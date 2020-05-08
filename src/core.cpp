#include "core.h"
#include "shader_source.h"
#include "constants.h"
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

        if (m_frameResized) {
            m_frameResized = false;

            // Update viewport
            glViewport(0, 0, config.frameWidth, config.frameHeight);

            logInfo("Resized to " + std::to_string(config.frameWidth) + "x" + std::to_string(config.frameHeight));
        }

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
    // TODO: real game updates

    m_spriteBatch.clear();

    u32 w = 1;
    u32 h = 1;
    constexpr u32 n = 7;

    glm::vec4 colors[n] = {
            glm::vec4(1.00, 0.00, 0.00, 1.00), // red
            glm::vec4(1.00, 0.50, 0.00, 1.00), // orange
            glm::vec4(1.00, 1.00, 0.00, 1.00), // yellow
            glm::vec4(0.00, 1.00, 0.00, 1.00), // green
            glm::vec4(0.00, 0.00, 1.00, 1.00), // blue
            glm::vec4(0.25, 0.00, 1.00, 1.00), // indigo
            glm::vec4(0.30, 0.00, 0.50, 1.00), // violet
    };

    glm::vec2 bl = glm::vec2(w * n, h) * -0.5f;
    for (u32 i = 0; i < n; ++i) {
        m_spriteBatch.addSprite(bl + glm::vec2(w * i, 0), glm::vec2(w, h), colors[i]);
    }
}

void Core::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_spriteShader.bind();

    // calculate view matrix
    glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(-m_camera.position, 0));

    // calculate projection matrix
    f32 aspect_ratio = (f32) config.frameWidth / (f32) config.frameHeight;
    glm::mat4 proj = glm::ortho<float>(
            consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT * -0.5f * aspect_ratio * m_camera.distance,
            consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT *  0.5f * aspect_ratio * m_camera.distance,
            consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT * -0.5f * m_camera.distance,
            consts::DEFAULT_CAMERA_FRUSTUM_HEIGHT *  0.5f * m_camera.distance
    );

    // set view projection matrix
    m_spriteShader.setMat4("uViewProjectionMatrix", proj * view);

    // Texture atlas is bound to texture unit 0
    m_spriteShader.setInt("uAtlas", 0);

    // Draw sprites
    m_spriteBatch.draw();

    // TODO: more sophisticated rendering system for different textures
}
