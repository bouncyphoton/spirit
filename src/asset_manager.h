#ifndef SPIRIT_ASSET_MANAGER_H
#define SPIRIT_ASSET_MANAGER_H

#include "tile.h"
#include "entity.h"
#include "texture_atlas.h"
#include <glm/glm.hpp>

class AssetManager {
public:
    AssetManager() = default;

    void init();

    void destroy();

    glm::vec4 getTileUv(Tile &tile);
    u8 getNumVariants(TileIdEnum id);

    glm::vec4 getEntityUv(Entity &entity);
    u8 getNumFrames(EntityIdEnum id);

private:
    TextureAtlas m_textureAtlas;
    std::vector<std::vector<glm::vec4>> m_tileUvs;
    std::vector<std::vector<glm::vec4>> m_entityUvs;
};

#endif //SPIRIT_ASSET_MANAGER_H
