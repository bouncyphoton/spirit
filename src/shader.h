#ifndef SPIRIT_SHADER_H
#define SPIRIT_SHADER_H

#include "types.h"
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    void init(const char *vertex_src, const char *fragment_src);

    void destroy();

    void bind();

    void setMat4(const std::string &uniform_name, glm::mat4 value);

    void setInt(const std::string &uniform_name, s32 value);

    void setFloat(const std::string &uniform_name, f32 value);

private:
    static void checkCompileStatus(u32 shader);

    static void checkLinkStatus(u32 program);

    u32 m_programId = 0;
};

#endif //SPIRIT_SHADER_H
