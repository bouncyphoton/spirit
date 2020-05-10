#include "asset_manager.h"
#include "constants.h"
#include "core.h"

void AssetManager::init() {
    m_textureAtlas.init("../assets/", 16, 16);

    // Go over each tile
    m_tileUvs.reserve(tileInfoList.size());
    for (TileInfo tile : tileInfoList) {
        // Associate uvs in texture atlas with texture variants
        m_tileUvs.emplace_back();
        m_tileUvs.back().reserve(tile.numVariants);
        for (u32 i = 0; i < tile.numVariants; ++i) {
            // Get uv by name
            std::string name = tile.textureBaseName + std::to_string(i) + consts::TEXTURE_EXTENSION;
            glm::vec4 uv = m_textureAtlas.getUv(name);
            m_tileUvs.back().emplace_back(uv);
        }
    }
}

void AssetManager::destroy() {
    m_textureAtlas.destroy();
}

glm::vec4 AssetManager::getTileUv(Tile &tile) {
    if (tile.id >= m_tileUvs.size()) {
        core->logWarn("Tried to get UV of unknown id: " + std::to_string(tile.id));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    if (tile.variant >= m_tileUvs[tile.id].size()) {
        core->logWarn("Tried to get UV of tile with invalid variant: "
                      + std::to_string(tile.id) + ":" + std::to_string(tile.variant));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    return m_tileUvs[tile.id][tile.variant];
}

u32 AssetManager::getNumVariants(TileIdEnum id) {
    if (id > m_tileUvs.size()) {
        core->logWarn("Tried to get variants of unknown id: " + std::to_string(id));
        return 0;
    }

    return m_tileUvs[id].size();
}
