#include "playerConfig.h"

void PlayerConfig_init(PlayerConfig *playerConfig) {
    playerConfig->seed = 0;
    playerConfig->sound = true;
    playerConfig->volume = 85;
    playerConfig->horizontalSens = 5;
    playerConfig->verticalSens = 5;
}
