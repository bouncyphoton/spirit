#include "core.h"
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

        update();

        render();

        m_platform.swapBuffers();
    }
}

void Core::quit() {
    cleanup();
    exit(0);
}

void Core::logFatal(const std::string& msg) {
    std::cout << "[fatal] " << msg << std::endl;
    cleanup();
    exit(1);
}

void Core::logInfo(const std::string &msg) {
    std::cout << "[info] " << msg << std::endl;
}

void Core::init() {
    // TODO: load this config from somewhere
    config.windowWidth = 1280;
    config.windowHeight = 720;

    m_platform.init();
}

void Core::cleanup() {
    m_platform.destroy();
}

void Core::update() {
    // TODO
}

void Core::render() {
    // TODO
}
