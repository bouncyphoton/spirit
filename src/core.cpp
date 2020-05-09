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

        if (frameResized) {
            frameResized = false;

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

    m_camera.position = glm::vec2(4, 4);

    m_platform.init();
    m_spriteShader.init(sprite_vertex_src, sprite_fragment_src);
    textureAtlas.init("../assets/", 16, 16);
    m_world.init();
}

void Core::cleanup() {
    m_world.destroy();
    textureAtlas.destroy();
    m_spriteShader.destroy();
    m_platform.destroy();
}

void Core::update() {
    // TODO: real game updates
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

    m_world.draw();

    // TODO: more sophisticated rendering system for different textures
}
