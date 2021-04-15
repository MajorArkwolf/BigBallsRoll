#pragma once
#include "stdbool.h"

typedef struct PlayerConfig {
    int seed;
    int volume;
    bool sound;
    int verticalSens;
    int horizontalSens;
    char name[256];
    int nameLength;
    int levels;
    int width;
    int height;
    bool horizontalLock;
    bool windowedMode;
} PlayerConfig;

void PlayerConfig_init(PlayerConfig *playerConfig);
