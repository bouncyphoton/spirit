#include "asset_manager.h"
#include "sprite.h"
#include "constants.h"

void AssetManager::init() {
    m_textureAtlas.init("../assets/", 16, 16);

    // Built in sprites are a special case
    for (u32 i = 0; i < NUM_BUILT_IN_SPRITES; ++i) {
        assert(i == spriteMetadata[i].id);
        m_uvs.emplace_back();

        m_uvs.back().emplace_back(m_textureAtlas.getUv(spriteMetadata[i].textureBaseName));
    }

    // Non-built in sprites
    for (u32 i = NUM_BUILT_IN_SPRITES; i < NUM_SPRITES; ++i) {
        assert(i == spriteMetadata[i].id);
        m_uvs.emplace_back();

        for (u32 j = 0; j < spriteMetadata[i].numVariants; ++j) {
            std::string textureName = spriteMetadata[i].textureBaseName
                                      + std::to_string(j) + consts::TEXTURE_EXTENSION;
            m_uvs.back().emplace_back(m_textureAtlas.getUv(textureName));
        }
    }
}

void AssetManager::destroy() {
    m_textureAtlas.destroy();
}

glm::vec4 AssetManager::getUv(u32 spriteId, u32 variant) {
    return m_uvs[spriteId][variant];
}

u32 AssetManager::getNumVariants(u32 spriteId) {
    return m_uvs[spriteId].size();
}
