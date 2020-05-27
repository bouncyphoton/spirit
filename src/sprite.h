#ifndef SPIRIT_SPRITE_H
#define SPIRIT_SPRITE_H

#include "types.h"
#include "constants.h"

struct SpriteMetadata {
    u32 id;
    u32 numVariants;
    const char *textureBaseName;
};

enum SpriteBuiltInEnum {
    SPRITE_MISSING,
    SPRITE_WHITE,
    NUM_BUILT_IN_SPRITES
};

enum SpriteEnum {
    SPRITE_GRASS = NUM_BUILT_IN_SPRITES,
    SPRITE_FLOWER,
    SPRITE_ROCK,
    NUM_SPRITES
};

const static SpriteMetadata spriteMetadata[] = {
        {SPRITE_MISSING, 1, consts::MISSING_TEXTURE_NAME},
        {SPRITE_WHITE,   1, consts::WHITE_TEXTURE_NAME},
        {SPRITE_GRASS,   1, "grass"},
        {SPRITE_FLOWER,  1, "flower"},
        {SPRITE_ROCK,    2, "rock"},
};

#endif //SPIRIT_SPRITE_H
