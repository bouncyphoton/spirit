#ifndef SPIRIT_CORE_H
#define SPIRIT_CORE_H

class Core {
public:
    Core() = default;

    [[noreturn]] void run();

    [[noreturn]] void quit();
private:
    void init();

    void cleanup();

    void update();

    void render();

    bool m_running = true;
};

extern Core *core;

#endif //SPIRIT_CORE_H
