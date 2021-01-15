#pragma once
#include "sound.h"

#define MAX_SOUNDS 1000

typedef struct AudioManager {
    Sound Sounds[MAX_SOUNDS];
    size_t NumOfSounds;
    char *cwd;
} AudioManager;

void AudioManager_init(AudioManager *audioManager);

void AudioManager_loadSounds(AudioManager *audioManager, char *cwd);

//TODO: Find sound, return ID function

void AudioManager_free(AudioManager *audioManager);