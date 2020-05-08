#ifndef SPIRIT_CORE_H
#define SPIRIT_CORE_H

#include "platform.h"
#include "shader.h"
#include "sprite_batch.h"
#include "camera.h"
#include <string>

class Core {
public:
    Core() = default;

    [[noreturn]] void run();

    [[noreturn]] void quit();

    [[noreturn]] void logFatal(const std::string& msg);

    void logInfo(const std::string& msg);

    Config config = {};
    bool m_frameResized = true;
private:
    void init();

    void cleanup();

    void update();

    void render();

    Platform m_platform;
    Shader m_spriteShader;
    SpriteBatch m_spriteBatch;

    Camera m_camera;
};

extern Core *core;

#endif //SPIRIT_CORE_H
