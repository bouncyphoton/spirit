#ifndef SPIRIT_ASSET_MANAGER_H
#define SPIRIT_ASSET_MANAGER_H

#include "texture_atlas.h"
#include <glm/glm.hpp>
#include <vector>

class AssetManager {
public:
    AssetManager() = default;

    void init();

    void destroy();

    glm::vec4 getUv(u32 spriteId, u32 variant = 0);

    u32 getNumVariants(u32 spriteId);

private:
    TextureAtlas m_textureAtlas;

    // first index is id, second index is variant
    std::vector<std::vector<glm::vec4>> m_uvs;
};

#endif //SPIRIT_ASSET_MANAGER_H
