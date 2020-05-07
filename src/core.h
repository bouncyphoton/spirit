#ifndef SPIRIT_CORE_H
#define SPIRIT_CORE_H

#include "platform.h"
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
};

extern Core *core;

#endif //SPIRIT_CORE_H
