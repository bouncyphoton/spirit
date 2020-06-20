#include "platform.h"
#include "core.h"
#include "constants.h"
#include <GL/gl3w.h>

void Platform::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        core->logFatal("Failed to init SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, consts::OPENGL_VERSION_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, consts::OPENGL_VERSION_MINOR);

    // sdl window
    m_window = SDL_CreateWindow("spirit",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                core->config.frameWidth, core->config.frameHeight,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        core->logFatal("Failed to create window");
    }

    // opengl context
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext) {
        core->logFatal("Failed to create OpenGL context");
    }

    // gl3w
    if (gl3wInit()) {
        core->logFatal("Failed to initialize gl3w");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GL_SetSwapInterval(1);
}

void Platform::destroy() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Platform::update() {
    // Update delta time
    auto prev = m_lastUpdate;
    m_lastUpdate = std::chrono::system_clock::now();
    m_frameTime = std::chrono::duration_cast<std::chrono::microseconds>(m_lastUpdate - prev).count() / 1000.0f;
    m_deltaTime = m_frameTime / (1000.0f / consts::TARGET_HERTZ);

    // Change "pressed" states to "down" states
    for (auto &keyState : m_keyStates) {
        if (keyState.second == KeyStateEnum::PRESSED) {
            keyState.second = KeyStateEnum::DOWN;
        }
    }

    // Poll events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                core->quit();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        core->platformEventFlags |= FRAME_RESIZED;
                        core->config.frameWidth = event.window.data1;
                        core->config.frameHeight = event.window.data2;
                        break;
                }
                break;
            case SDL_KEYDOWN:
                if (m_keyStates[event.key.keysym.sym] == KeyStateEnum::UP) {
                    m_keyStates[event.key.keysym.sym] = KeyStateEnum::PRESSED;
                }
                break;
            case SDL_KEYUP:
                m_keyStates[event.key.keysym.sym] = KeyStateEnum::UP;
                break;
        }
    }
}

void Platform::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

f32 Platform::getDeltaTime() {
    return m_deltaTime;
}

f32 Platform::getFrameTime() {
    return m_frameTime;
}

bool Platform::isKeyPressed(u32 key) {
    return m_keyStates[key] == KeyStateEnum::PRESSED;
}

bool Platform::isKeyDown(u32 key) {
    return m_keyStates[key] != KeyStateEnum::UP;
}
