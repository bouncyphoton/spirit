#include "platform.h"
#include "core.h"
#include "defines.h"
#include <GL/gl3w.h>

void Platform::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        core->logFatal("Failed to init SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_VERSION_MAJOR);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR);

    // sdl window
    m_window = SDL_CreateWindow("spirit",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                core->config.windowWidth, core->config.windowHeight, SDL_WINDOW_OPENGL);
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
}

void Platform::destroy() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Platform::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            core->quit();
        }
        // TODO: process events
    }
}

void Platform::swapBuffers() {
    SDL_GL_SwapWindow(m_window);
}
