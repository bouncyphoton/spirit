#include "tile.h"

// { u32 id, u32 numVariants, str textureBaseName }
// { 0, 2, "foo" } will associate the id with the textures "foo0.png" and "foo1.png"
// numVariants should be at least 1
std::vector<TileInfo> tileInfoList = {
        {GRASS_ID, 6, "grass"}
};
