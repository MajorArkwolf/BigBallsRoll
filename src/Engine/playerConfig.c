#include "playerConfig.h"
#include <string.h>

void PlayerConfig_init(PlayerConfig *playerConfig) {
    playerConfig->seed = 0;
    playerConfig->horizontalSens = 5;
    playerConfig->verticalSens = 5;
    playerConfig->levels = 3;
    playerConfig->width = 1920;
    playerConfig->height = 1080;
    playerConfig->horizontalLock = false;
    playerConfig->windowedMode = true;
    strcpy(playerConfig->name, "BallMaster27");
    playerConfig->nameLength = 12;
}
