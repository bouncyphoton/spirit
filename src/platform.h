#ifndef SPIRIT_PLATFORM_H
#define SPIRIT_PLATFORM_H

#include "config.h"
#include <SDL.h>
#include <chrono>
#include <unordered_map>

class Platform {
public:
    void init();

    void destroy();

    void update();

    void swapBuffers();

    f32 getDeltaTime();

    f32 getFrameTime();

    bool isKeyPressed(u32 key);

    bool isKeyDown(u32 key);

private:
    enum class KeyStateEnum {
        UP,
        DOWN,
        PRESSED,
    };

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
    std::chrono::system_clock::time_point m_lastUpdate;
    f32 m_deltaTime;
    f32 m_frameTime;
    std::unordered_map<u32, KeyStateEnum> m_keyStates;
};

#endif //SPIRIT_PLATFORM_H
