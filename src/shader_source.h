#ifndef SPIRIT_SHADER_SOURCE_H
#define SPIRIT_SHADER_SOURCE_H

// These shaders are trivial, no need to load them from a file or anything

const char *sprite_vertex_src = R"(#version 330 core
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec4 aColor;

out VertexData {
    vec2 position;
    vec2 uv;
    vec4 color;
} o;

uniform mat4 uViewProjectionMatrix;

void main() {
    o.position = aPosition;
    o.uv = aUv;
    o.color = aColor;

    gl_Position = uViewProjectionMatrix * vec4(aPosition, 0, 1);
}
)";

const char *sprite_fragment_src = R"(#version 330 core
layout (location = 0) out vec4 oFragColor;

in VertexData {
    vec2 position;
    vec2 uv;
    vec4 color;
} i;

uniform sampler2D uAtlas;
uniform sampler2D uDataAtlas;

void main() {
    vec4 data = texture(uDataAtlas, i.uv);

    // Lots of temporary code here
    vec3 N = normalize(data.xyz * 2 - 1); // [0, 1] -> [-1, 1]
    vec3 L = -normalize(vec3(2, 1, -0.1));
    vec2 lightPos = vec2(2, 10);
    float cosTheta = max(0.1, dot(N, L));

    // Attenuation calculation
    float theta = dot(L, -normalize(vec3(i.position - lightPos, 0)));
    float dist = length(i.position - lightPos);
    float falloff = clamp((theta - 0.8) / 0.1, 0, 1);
    float atten = 10 / (dist * dist + 1) * falloff;

    vec4 color = texture(uAtlas, i.uv) * i.color;

    oFragColor = color * atten * mix(vec4(1), vec4(vec3(cosTheta), 1), data.w);
}
)";

#endif //SPIRIT_SHADER_SOURCE_H
