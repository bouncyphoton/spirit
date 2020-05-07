#include "core.h"
#include <cstdlib>

static Core core_local;
Core *core = &core_local;

void Core::run() {
    init();

    while (m_running) {
        // TODO: poll input

        update();

        render();

        // TODO: swap buffers
    }

    quit();
}

void Core::quit() {
    cleanup();
    exit(0);
}

void Core::init() {
    // TODO
}

void Core::cleanup() {
    // TODO
}

void Core::update() {
    // TODO
}

void Core::render() {
    // TODO
}
