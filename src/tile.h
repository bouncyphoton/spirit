#ifndef SPIRIT_TILE_H
#define SPIRIT_TILE_H

#include "types.h"
#include <string>
#include <vector>

enum TileIdEnum : u32 {
    GRASS_ID,
    NUM_TILES
};

struct TileInfo {
    TileIdEnum id;
    u32 numVariants;
    std::string textureBaseName;
};

struct Tile {
    TileIdEnum id;
    u8 variant;
};

extern std::vector<TileInfo> tileInfoList;

#endif //SPIRIT_TILE_H
