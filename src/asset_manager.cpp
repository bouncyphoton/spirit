#include "asset_manager.h"
#include "constants.h"
#include "core.h"

void AssetManager::init() {
    m_textureAtlas.init("../assets/", 16, 16);

    // TODO: see if tile and entity management can be combined due to similarities

    // Go over each tile
    m_tileUvs.reserve(tileInfoList.size());
    for (TileInfo &tile : tileInfoList) {
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

    // Go over each entity
    m_entityUvs.reserve(entityInfoList.size());
    for (EntityInfo &entity : entityInfoList) {
        // Associate uvs in texture atlas with frames of entity
        m_entityUvs.emplace_back();
        m_entityUvs.back().reserve(entity.numFrames);
        for (u32 i = 0; i < entity.numFrames; ++i) {
            // Get uv by name
            std::string name = entity.textureBaseName + std::to_string(i) + consts::TEXTURE_EXTENSION;
            glm::vec4 uv = m_textureAtlas.getUv(name);
            m_entityUvs.back().emplace_back(uv);
        }
    }
}

void AssetManager::destroy() {
    m_textureAtlas.destroy();
}

glm::vec4 AssetManager::getWhiteUv() {
    return m_textureAtlas.getUv(consts::WHITE_TEXTURE_NAME);
}

glm::vec4 AssetManager::getTileUv(Tile &tile) {
    if (tile.id >= m_tileUvs.size()) {
        core->logWarn("Tried to get UV of unknown tile id: " + std::to_string(tile.id));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    if (tile.variant >= m_tileUvs[tile.id].size()) {
        core->logWarn("Tried to get UV of tile with invalid variant: "
                      + std::to_string(tile.id) + ":" + std::to_string(tile.variant));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    return m_tileUvs[tile.id][tile.variant];
}

u8 AssetManager::getNumVariants(TileIdEnum id) {
    if (id > m_tileUvs.size()) {
        core->logWarn("Tried to get variants of unknown tile id: " + std::to_string(id));
        return 0;
    }

    return m_tileUvs[id].size();
}

glm::vec4 AssetManager::getEntityUv(Entity &entity) {
    if (entity.id >= m_entityUvs.size()) {
        core->logWarn("Tried to get UV of unknown entity id: " + std::to_string(entity.id));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    if (entity.frame >= m_entityUvs[entity.id].size()) {
        core->logWarn("Tried to get UV of entity with invalid frame: "
                      + std::to_string(entity.id) + ":" + std::to_string(entity.frame));
        return m_textureAtlas.getUv(consts::MISSING_TEXTURE_NAME);
    }

    return m_entityUvs[entity.id][entity.frame];
}

u8 AssetManager::getNumFrames(EntityIdEnum id) {
    if (id > m_entityUvs.size()) {
        core->logWarn("Tried to get variants of unknown entity id: " + std::to_string(id));
        return 0;
    }

    return m_entityUvs[id].size();
}
