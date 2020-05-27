#include "texture_atlas.h"
#include "core.h"
#include <GL/gl3w.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <filesystem>
#include <vector>

void TextureAtlas::init(const std::string &directory, s32 textureSideLength) {
    if (textureSideLength <= 0) {
        core->logFatal("Cannot create texture atlas out of textures with non-positive sides");
    }

    std::filesystem::path dir(directory);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        core->logFatal("Texture atlas directory is not valid");
    }

    // Useful variables
    u32 bytesPerPixel = 4;
    u32 textureStride = textureSideLength * bytesPerPixel;
    u32 bytesPerTexture = textureStride * textureSideLength;

    // Holds texture data while we're creating our atlas
    std::vector<u8 *> textureData;
    std::vector<std::string> textureNames;

    // Not entirely necessary, but minimizes typos
    auto addTexture = [&](const char *textureName, u8 *data) {
        textureNames.emplace_back(textureName);
        textureData.emplace_back(data);
    };

    // Missing texture
    {
        // Allocate memory
        u8 *missingTextureData = (u8 *) calloc(bytesPerTexture, sizeof(u8));
        if (!missingTextureData) {
            core->logFatal("Failed to allocate memory for missing texture data");
        }

        // Set data
        for (u32 i = 0; i < bytesPerTexture; i += bytesPerPixel) {
            u32 x = (i / bytesPerPixel) % textureSideLength;
            u32 y = (i / bytesPerPixel) / textureSideLength;

            missingTextureData[i + 3] = 255;
            if ((x >= textureSideLength / 2 && y < textureSideLength / 2)
                || (x < textureSideLength / 2 && y >= textureSideLength / 2)) {
                missingTextureData[i + 0] = 255;
                missingTextureData[i + 2] = 255;
            }
        }

        // Add texture, we don't want to free our data until the end
        addTexture(consts::MISSING_TEXTURE_NAME, missingTextureData);
    }

    // White texture
    {
        // Allocate memory
        u8 *whiteTextureData = (u8 *) malloc(bytesPerTexture * sizeof(u8));
        if (!whiteTextureData) {
            core->logFatal("Failed to allocate memory for missing texture data");
        }

        // Set data
        memset(whiteTextureData, 255, bytesPerTexture * sizeof(u8));

        // Add texture
        addTexture(consts::WHITE_TEXTURE_NAME, whiteTextureData);
    }

    // Load textures from assets directory
    stbi_set_flip_vertically_on_load(1);

    // Iterate asset directory recursively
    for (auto &p : std::filesystem::recursive_directory_iterator(dir)) {
        // Ignore files with incorrect extension
        if (p.path().extension() != consts::TEXTURE_EXTENSION) {
            continue;
        }

        std::string pathStr = p.path().string();
        std::string textureName = pathStr.substr(directory.length());

        // Load texture data
        s32 w, h;
        u8 *data = stbi_load(pathStr.c_str(), &w, &h, nullptr, bytesPerPixel);

        // Skip non-square textures or textures with incorrect side lengths
        if (w != h || w != textureSideLength) {
            free(data);
            continue;
        }

        addTexture(textureName.c_str(), data);
    }

    // Generate texture atlas
    core->logInfo("Creating texture atlas with "
                  + std::to_string(textureData.size()) + " "
                  + std::to_string(textureSideLength) + "x" + std::to_string(textureSideLength)
                  + " textures");

    // Calculate how large the atlas is
    u32 atlasTexturesPerSide = ceil(sqrtf(textureData.size()));
    u32 atlasSideLength = atlasTexturesPerSide * textureSideLength;
    u32 atlasStride = atlasSideLength * bytesPerPixel;

    // One quarter of a texel
    f32 uvEpsilon = 1.0f / (atlasSideLength * 4.0f);

    // Allocate memory for the atlas
    u8 *atlasData = (u8 *) calloc(atlasSideLength * atlasStride, sizeof(u8));
    if (!atlasData) {
        core->logFatal("Failed to allocate memory for texture atlas");
    }

    // Iterate over all our textures
    for (u32 i = 0; i < textureData.size(); ++i) {
        // Turn flat texture index to 2D coordinate
        u32 textureX = i % atlasTexturesPerSide;
        u32 textureY = i / atlasTexturesPerSide;

        // Set UV coordinates
        m_uvMap[textureNames[i]] = glm::vec4(
                textureX + uvEpsilon,
                textureY + uvEpsilon,
                textureX + 1.0f - uvEpsilon,
                textureY + 1.0f - uvEpsilon
        ) / glm::vec4(atlasTexturesPerSide);

        // Get pointers to destination in atlas data and source texture data
        u8 *dst = atlasData
                  + textureX * textureStride
                  + textureY * atlasStride * textureSideLength;
        u8 *src = textureData[i];

        // Copy texture data
        for (u32 j = 0; j < textureSideLength; ++j) {
            memcpy(dst, src, textureStride);
            src += textureStride;
            dst += atlasStride;
        }
    }

    // Send atlas texture to the GPU and bind to texture unit 0
    glGenTextures(1, &m_textureId);
    if (m_textureId == 0) {
        core->logFatal("Failed to generate OpenGL texture for texture atlas");
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasSideLength, atlasSideLength, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlasData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Free data
    free(atlasData);
    for (auto &data : textureData) {
        free(data);
    }
}

void TextureAtlas::destroy() {
    glDeleteTextures(1, &m_textureId);
}

glm::vec4 TextureAtlas::getUv(const std::string &name) {
    if (m_uvMap.find(name) == m_uvMap.end()) {
        core->logWarn("Texture \"" + name + "\" not found in atlas");
        m_uvMap[name] = m_uvMap[consts::MISSING_TEXTURE_NAME];
    }
    return m_uvMap[name];
}
