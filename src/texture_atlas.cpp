#include "texture_atlas.h"
#include "core.h"
#include <GL/gl3w.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include <filesystem>
#include <vector>

// TODO: Improve significantly, this is a HUGE mess

void TextureAtlas::init(const std::string &directory, s32 w, s32 h) {
    stbi_set_flip_vertically_on_load(1);

    std::filesystem::path dir(directory);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir)) {
        core->logFatal("Texture atlas directory is not valid");
    }

    // Load texture data for textures we want (first is texture, second is extra data)
    std::vector<std::pair<u8 *, u8 *>> textureData;
    std::unordered_map<std::string, u32> textureIndices;

    // Allocate missing texture data
    u8 *missingTextureData = (u8 *) calloc(w * h * 4, sizeof(u8));
    if (!missingTextureData) {
        core->logFatal("Failed to allocate memory for missing texture data");
    }
    // Generate missing texture data
    for (u32 i = 0; i < w * h * 4; i += 4) {
        u32 x = (i / 4) % w;
        u32 y = (i / 4) / w;
        missingTextureData[i + 3] = 255;
        if ((x >= w / 2 && y < h / 2) || (x < w / 2 && y >= h / 2)) {
            missingTextureData[i + 0] = 255;
            missingTextureData[i + 2] = 255;
        }
    }
    // Add missing texture
    textureIndices[consts::MISSING_TEXTURE_NAME] = textureData.size();
    textureData.emplace_back(missingTextureData, nullptr);

    // Add white texture
    u8 *whiteTextureData = (u8 *) calloc(w * h * 4, sizeof(u8));
    if (!whiteTextureData) {
        core->logFatal("Failed to allocate memory for missing texture data");
    }
    for (u32 i = 0; i < w * h * 4; ++i) {
        whiteTextureData[i] = 255;
    }
    textureIndices[consts::WHITE_TEXTURE_NAME] = textureData.size();
    textureData.emplace_back(whiteTextureData, nullptr);

    // Add textures in given directory
    for (auto &p : std::filesystem::recursive_directory_iterator(dir)) {
        // Ignore non-png files
        if (p.path().extension() != consts::TEXTURE_EXTENSION) {
            continue;
        }

        // Ignore files with "extra" in them, as we'll pick them up anyway
        if (p.path().string().find("extra") != std::string::npos) {
            continue;
        }

        // Load texture data
        s32 currentW = 0, currentH = 0;
        u8 *data = stbi_load(p.path().u8string().c_str(), &currentW, &currentH, nullptr, 4);
        u8 *extraData = nullptr;

        std::string extraFileName = p.path().u8string().substr(
                0, p.path().u8string().length() - p.path().extension().u8string().length())
                                    + "_extra" + p.path().extension().u8string();
        if (std::filesystem::exists(extraFileName)) {
            s32 extraW, extraH;
            extraData = stbi_load(extraFileName.c_str(), &extraW, &extraH, nullptr, 4);

            if (currentW != extraW || currentH != extraH) {
                // Make later check fail
                currentW = w - 1;
            }
        }

        // Keep track of data if dimensions are correct, otherwise free
        if (currentW == w && currentH == h) {
            std::string textureName = p.path().string().substr(directory.length());

            textureIndices[textureName] = textureData.size();
            textureData.emplace_back(data, extraData);
        } else {
            free(data);
            free(extraData);
        }
    }

    core->logInfo("Creating texture atlas with " + std::to_string(textureData.size()) + " "
                  + std::to_string(w) + "x" + std::to_string(h) + " textures");

    // Generate texture data
    // TODO: assume textures are square for now
    assert(w == h);
    u32 sideLengthImages = ceil(sqrt(w * h * textureData.size()) / w);
    u32 sideLengthPixels = sideLengthImages * w;
    u8 *atlasTextureData = (u8 *) calloc(sideLengthPixels * sideLengthPixels * 4, sizeof(u8)); // RGBA8 pixels
    if (!atlasTextureData) {
        core->logFatal("Failed to allocate memory for atlas texture data");
    }

    // This holds data like world-space normals
    u8 *atlasExtraData = (u8 *) calloc(sideLengthPixels * sideLengthPixels * 4, sizeof(u8)); // RGBA8 pixels
    if (!atlasExtraData) {
        core->logFatal("Failed to allocate memory for atlas extra data");
    }

    // Set texture atlas data
    u32 atlasStride = sideLengthPixels * 4;
    for (u32 i = 0; i < textureData.size(); ++i) {
        // x and y coordinates for current texture in atlas
        u32 x = i % (sideLengthImages);
        u32 y = (sideLengthImages) - 1 - i / (sideLengthImages);

        u32 currentStartIdx = y * h * atlasStride + x * w * 4;

        // Iterate over each pixel component in texture
        for (u32 j = 0; j < w * h * 4; ++j) {
            u32 xSrc = j % (w * 4);
            u32 ySrc = j / (w * 4);

            u32 atlasIndex = currentStartIdx + xSrc + ySrc * atlasStride;
            atlasTextureData[atlasIndex] = textureData[i].first[j];
            if (textureData[i].second) {
                atlasExtraData[atlasIndex] = textureData[i].second[j];
            }
        }
    }

    // Get uvs for textures in atlas
    const f32 UV_EPSILON = 1.0f / sideLengthPixels / 4.0f;
    for (auto &t : textureIndices) {
        u32 i = t.second;
        u32 x = i % (sideLengthImages);
        u32 y = (sideLengthImages) - 1 - i / (sideLengthImages);


        m_uvMap[t.first] = glm::vec4(
                x + UV_EPSILON,
                y + UV_EPSILON,
                x + 1.0f - UV_EPSILON,
                y + 1.0f - UV_EPSILON
        ) / glm::vec4(sideLengthImages);
    }

    // Create main texture atlas
    {
        // Generate OpenGL texture
        glGenTextures(1, &m_textureId);
        if (m_textureId == 0) {
            core->logFatal("Failed to generate texture atlas OpenGL texture");
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sideLengthPixels, sideLengthPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     atlasTextureData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    // Create extra data atlas
    {
        // Generate OpenGL texture
        glGenTextures(1, &m_textureExtraId);
        if (m_textureExtraId == 0) {
            core->logFatal("Failed to generate texture data atlas OpenGL texture");
        }
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_textureExtraId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sideLengthPixels, sideLengthPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     atlasExtraData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    // Free data
    free(atlasTextureData);
    free(atlasExtraData);
    for (auto &data : textureData) {
        free(data.first);
        free(data.second);
    }
}

void TextureAtlas::destroy() {
    glDeleteTextures(1, &m_textureExtraId);
    glDeleteTextures(1, &m_textureId);
}

glm::vec4 TextureAtlas::getUv(const std::string &name) {
    if (m_uvMap.find(name) == m_uvMap.end()) {
        core->logWarn("Texture \"" + name + "\" not found in atlas");
        m_uvMap[name] = m_uvMap["*missing"];
    }
    return m_uvMap[name];
}
