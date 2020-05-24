#ifndef SPIRIT_ASSET_MANAGER_H
#define SPIRIT_ASSET_MANAGER_H

#include "texture_atlas.h"
#include "sprite.h"
#include <glm/glm.hpp>

class AssetManager {
public:
    void init();

    void destroy();

    // TODO: Optimize, this is expensive
    Sprite getSprite(const std::string &name);

private:
    TextureAtlas m_textureAtlas;
};

#endif //SPIRIT_ASSET_MANAGER_H
