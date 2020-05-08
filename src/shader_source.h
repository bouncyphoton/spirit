#ifndef SPIRIT_SHADER_SOURCE_H
#define SPIRIT_SHADER_SOURCE_H

// These shaders are trivial, no need to load them from a file or anything

const char *sprite_vertex_src = R"(#version 330 core
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec4 aColor;

out VertexData {
    vec2 uv;
    vec4 color;
} o;

uniform mat4 uViewProjectionMatrix;

void main() {
    o.uv = aUv;
    o.color = aColor;

    gl_Position = uViewProjectionMatrix * vec4(aPosition, 0, 1);
}
)";

const char *sprite_fragment_src = R"(#version 330 core
layout (location = 0) out vec4 oFragColor;

in VertexData {
    vec2 uv;
    vec4 color;
} i;

void main() {
    oFragColor = i.color;
}
)";

#endif //SPIRIT_SHADER_SOURCE_H
