#include "core.h"
#include "shader_source.h"
#include "constants.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl3w.h>
#include <cstdlib>
#include <iostream>

// ugh
#undef min
#undef max

static Core core_local;
Core *core = &core_local;

void Core::run() {
    init();

    logInfo("Initialized successfully");

    platformEventFlags |= FRAME_RESIZED;

    // Main loop runs until quit() is called
    while (true) {
        m_platform.update();

        if (platformEventFlags & FRAME_RESIZED) {
            platformEventFlags ^= FRAME_RESIZED;
            camera.aspectRatio = (f32) config.frameWidth / (f32) config.frameHeight;

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

void Core::logWarn(const std::string &msg) {
    std::cerr << "[warn] " << msg << std::endl;
}

void Core::init() {
    // TODO: load this config from somewhere
    config.frameWidth = 800;
    config.frameHeight = 600;

    camera.position = glm::vec2(consts::CHUNK_SIZE * consts::TILE_SIZE_METERS * 0.5f);

    m_platform.init();
    assetManager.init();
    m_spriteShader.init(sprite_vertex_src, sprite_fragment_src);
    debugBatch.init();

    m_world.init();
}

void Core::cleanup() {
    m_world.destroy();

    debugBatch.destroy();
    m_spriteShader.destroy();
    assetManager.destroy();
    m_platform.destroy();
}

void Core::update() {
    f32 dt = m_platform.getDeltaTime() / 60.0f * 2.4f;

    // Temp input and delta time test

    if (m_platform.isKeyDown(SDLK_w)) {
        camera.position.y += 1.0f * dt;
    }
    if (m_platform.isKeyDown(SDLK_d)) {
        camera.position.x += 1.0f * dt;
    }
    if (m_platform.isKeyDown(SDLK_s)) {
        camera.position.y -= 1.0f * dt;
    }
    if (m_platform.isKeyDown(SDLK_a)) {
        camera.position.x -= 1.0f * dt;
    }
    if (m_platform.isKeyDown(SDLK_q)) {
        camera.distance = glm::min(consts::CAMERA_MAX_DISTANCE, camera.distance + 1.0f * dt);
    }
    if (m_platform.isKeyDown(SDLK_e)) {
        camera.distance = glm::max(consts::CAMERA_MIN_DISTANCE, camera.distance - 1.0f * dt);
    }

    m_world.update();
}

void Core::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_spriteShader.bind();

    // Calculate view matrix
    glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(-camera.position, 0));

    // Calculate projection matrix
    Aabb bounds = camera.getCameraSpaceFrustumAabb();
    glm::mat4 proj = glm::ortho<f32>(bounds.min.x, bounds.max.x, bounds.min.y, bounds.max.y);

    // Set view projection matrix
    m_spriteShader.setMat4("uViewProjectionMatrix", proj * view);

    // Texture atlas is bound to texture unit 0
    m_spriteShader.setInt("uAtlas", 0);

    // Atlas with additional data is bound to texture unit 1
    m_spriteShader.setInt("uDataAtlas", 1);

    // Draw world (tiles and entities)
    m_world.draw();

    // Draw debug sprites
    debugBatch.draw();
    debugBatch.clear();
}
