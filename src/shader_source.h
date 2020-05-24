#ifndef SPIRIT_SHADER_SOURCE_H
#define SPIRIT_SHADER_SOURCE_H

// These shaders are trivial, no need to load them from a file or anything

const char *sprite_vertex_src = R"(#version 330 core
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aColorUv;
layout (location = 2) in vec2 aNormalUv;
layout (location = 3) in vec4 aColor;

out VertexData {
    vec2 position;
    vec2 colorUv;
    vec2 normalUv;
    vec4 color;
} o;

uniform mat4 uViewProjectionMatrix;

void main() {
    o.position = aPosition;
    o.colorUv = aColorUv;
    o.normalUv = aNormalUv;
    o.color = aColor;

    gl_Position = uViewProjectionMatrix * vec4(aPosition, 0, 1);
}
)";

const char *sprite_fragment_src = R"(#version 330 core
layout (location = 0) out vec4 oFragColor;

in VertexData {
    vec2 position;
    vec2 colorUv;
    vec2 normalUv;
    vec4 color;
} i;

uniform sampler2D uAtlas;
uniform float uTime;

// TODO: Lots of temporary code here
void main() {
    vec2 pos = floor(i.position * 16) / 16;

    float t = uTime;
    vec2 lightPos = vec2(7, -1) + vec2(cos(t), sin(t)) * 5;
    vec2 lightDir = normalize(vec2(-cos(t), -sin(t)));

    // surface normal vector
    vec2 N = normalize(texture(uAtlas, i.normalUv).xy * 2 - 1); // [0, 1] -> [-1, 1]

    // vector pointing from point to light
    vec2 L = normalize(vec2(lightPos - pos));

    // TODO: find a better solution
    // If there is no normal map, set N to L
    N = mix(L, N, texture(uAtlas, i.normalUv).w);

    // Attenuation calculation
    float theta = dot(-L, lightDir);
    float dist = distance(pos, lightPos);
    float falloff = clamp((theta - 0.8) / 0.1, 0, 1);
    float cosTheta = max(0.1, dot(N, L));
    float atten = 1 / (dist * dist + 1) * falloff * cosTheta;

    vec4 textureColor = texture(uAtlas, i.colorUv);
    vec3 color = pow(textureColor.xyz, vec3(2.2)) * i.color.xyz * atten;
    oFragColor = vec4(pow(color, vec3(1/2.2)), textureColor.w * i.color.w);
}
)";

#endif //SPIRIT_SHADER_SOURCE_H
