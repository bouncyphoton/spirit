#include "shader.h"
#include "core.h"
#include <GL/gl3w.h>
#include <vector>

void Shader::init(const char *vertex_src, const char *fragment_src) {
    m_programId = glCreateProgram();
    if (m_programId == 0) {
        core->logFatal("Failed to create shader program");
    }

    // Create and compile vertex shader
    u32 vert = glCreateShader(GL_VERTEX_SHADER);
    if (vert == 0) {
        core->logFatal("Failed to create vertex shader");
    }
    glShaderSource(vert, 1, &vertex_src, nullptr);
    glCompileShader(vert);
    checkCompileStatus(vert);
    glAttachShader(m_programId, vert);

    // Create and compile fragment shader
    u32 frag = glCreateShader(GL_FRAGMENT_SHADER);
    if (frag == 0) {
        core->logFatal("Failed to create fragment shader");
    }
    glShaderSource(frag, 1, &fragment_src, nullptr);
    glCompileShader(frag);
    checkCompileStatus(frag);
    glAttachShader(m_programId, frag);

    // Link program
    glLinkProgram(m_programId);
    glDetachShader(m_programId, vert);
    glDetachShader(m_programId, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);
    checkLinkStatus(m_programId);
}

void Shader::destroy() {
    glDeleteProgram(m_programId);
}

void Shader::bind() {
    glUseProgram(m_programId);
}

void Shader::checkCompileStatus(u32 shader) {
    s32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> log(length);
        glGetShaderInfoLog(shader, length, &length, log.data());

        core->logFatal("Failed to compile shader:\n" + std::string(log.data()));
    }
}

void Shader::checkLinkStatus(u32 program) {
    s32 success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::vector<char> log(length);
        glGetProgramInfoLog(program, length, &length, log.data());

        core->logFatal("Failed to link program:\n" + std::string(log.data()));
    }
}

void Shader::setMat4(const std::string &uniform_name, glm::mat4 value) {
    s32 loc = glGetUniformLocation(m_programId, uniform_name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
}

void Shader::setInt(const std::string &uniform_name, s32 value) {
    s32 loc = glGetUniformLocation(m_programId, uniform_name.c_str());
    glUniform1i(loc, value);
}

void Shader::setFloat(const std::string &uniform_name, f32 value) {
    s32 loc = glGetUniformLocation(m_programId, uniform_name.c_str());
    glUniform1f(loc, value);
}
