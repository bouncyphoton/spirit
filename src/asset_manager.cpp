#include "asset_manager.h"
#include "constants.h"

void AssetManager::init() {
    m_textureAtlas.init("../assets/", 16, 16);
}

void AssetManager::destroy() {
    m_textureAtlas.destroy();
}

Sprite AssetManager::getSprite(const std::string &name) {
    Sprite sprite = {};
    sprite.colorUv = m_textureAtlas.getUv(name + "_col" + consts::TEXTURE_EXTENSION);
    sprite.normalUv = m_textureAtlas.getUv(name + "_nrm" + consts::TEXTURE_EXTENSION);
    return sprite;
}
