#ifndef SPIRIT_PLATFORM_H
#define SPIRIT_PLATFORM_H

#include "config.h"
#include <SDL.h>

class Platform {
public:
    Platform() = default;

    void init();

    void destroy();

    void update();

    void swapBuffers();

private:
    SDL_Window *m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
};

#endif //SPIRIT_PLATFORM_H
