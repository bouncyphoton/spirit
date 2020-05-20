#ifndef SPIRIT_CORE_H
#define SPIRIT_CORE_H

#include "platform.h"
#include "shader.h"
#include "texture_atlas.h"
#include "asset_manager.h"
#include "camera.h"
#include "sprite_batch.h"
#include "world.h"
#include <string>

struct FrameStats {
    u32 chunksDrawn = 0;
};

class Core {
public:
    Core() = default;

    [[noreturn]] void run();

    [[noreturn]] void quit();

    [[noreturn]] void logFatal(const std::string &msg);

    void logInfo(const std::string &msg);

    void logWarn(const std::string &msg);

    Config config = {};
    FrameStats frameStats = {};
    AssetManager assetManager;
    Camera camera;
    SpriteBatch debugBatch;
    bool frameResized = true;
private:

    void init();

    void cleanup();

    void update();

    void render();

    Platform m_platform;
    Shader m_spriteShader;

    World m_world;
};

extern Core *core;

#endif //SPIRIT_CORE_H
