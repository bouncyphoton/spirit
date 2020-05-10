#ifndef SPIRIT_ASSET_MANAGER_H
#define SPIRIT_ASSET_MANAGER_H

#include "tile.h"
#include "texture_atlas.h"
#include <glm/glm.hpp>

class AssetManager {
public:
    AssetManager() = default;

    void init();

    void destroy();

    glm::vec4 getTileUv(Tile &tile);
    u32 getNumVariants(TileIdEnum id);
private:
    TextureAtlas m_textureAtlas;
    std::vector<std::vector<glm::vec4>> m_tileUvs;
};

#endif //SPIRIT_ASSET_MANAGER_H
