#ifndef SPIRIT_TEXTURE_ATLAS_H
#define SPIRIT_TEXTURE_ATLAS_H

#include "types.h"
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class TextureAtlas {
public:
    TextureAtlas() = default;

    void init(const std::string &directory, s32 w, s32 h);

    void destroy();

    glm::vec4 getUv(const std::string &name);

private:
    u32 m_textureId = 0;
    u32 m_textureExtraId = 0;
    std::unordered_map<std::string, glm::vec4> m_uvMap;
};

#endif //SPIRIT_TEXTURE_ATLAS_H
