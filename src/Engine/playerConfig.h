#pragma once
#include "stdbool.h"

#define NAME_SIZE 256

typedef struct PlayerConfig {
    int seed;
    int verticalSens;
    int horizontalSens;
    char name[NAME_SIZE];
    int nameLength;
    int levels;
    int width;
    int height;
    bool horizontalLock;
    bool windowedMode;
} PlayerConfig;

void PlayerConfig_init(PlayerConfig *playerConfig);
