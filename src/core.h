#ifndef SPIRIT_CORE_H
#define SPIRIT_CORE_H

#include "platform.h"
#include "shader.h"
#include "sprite_batch.h"
#include <string>

class Core {
public:
    Core() = default;

    [[noreturn]] void run();

    [[noreturn]] void quit();

    [[noreturn]] void logFatal(const std::string& msg);

    void logInfo(const std::string& msg);

    Config config = {};
private:
    void init();

    void cleanup();

    void update();

    void render();

    Platform m_platform;
    Shader m_spriteShader;
    SpriteBatch m_spriteBatch;
};

extern Core *core;

#endif //SPIRIT_CORE_H
