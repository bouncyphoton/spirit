#ifndef SPIRIT_SPRITE_H
#define SPIRIT_SPRITE_H

#include "types.h"

struct SpriteMetadata {
    u32 id;
    u32 numVariants;
    const char *textureBaseName;
};

enum SpriteId {
    SPRITE_GRASS,
    SPRITE_FLOWER,
    SPRITE_ROCK,
};

const static SpriteMetadata spriteMetadata[] = {
        {SPRITE_GRASS,  1, "grass"},
        {SPRITE_FLOWER, 1, "flower"},
        {SPRITE_ROCK,   2, "rock"},
};

#endif //SPIRIT_SPRITE_H
