#pragma once
#include "stdbool.h"

typedef struct PlayerConfig {
    int seed;
    int volume;
    bool sound;
    int verticalSens;
    int horizontalSens;
} PlayerConfig;

void PlayerConfig_init(PlayerConfig *playerConfig);
