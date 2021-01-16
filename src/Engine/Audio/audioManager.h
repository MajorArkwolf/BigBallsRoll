#pragma once
#include "sound.h"
#include <stdlib.h>

#define MAX_SOUNDS 1000

typedef struct AudioManager {
    Sound Sounds[MAX_SOUNDS];
    size_t NumOfSounds;
    char *cwd;
} AudioManager;

/**
 * Initialised the AudioManager for future use.
 * @param audioManager AudioManager struct to initialise.
 */
void AudioManager_init(AudioManager *audioManager);

/**
 * Preloads all the sounds found in the res/Loader/modelloading.txt
 * @param audioManager AudioManager to store all the Sounds into.
 * @param cwd current working directory relative to the executable.
 */
void AudioManager_loadSounds(AudioManager *audioManager, char *cwd);

/**
 * Search the AudioManager and return the buffer ID where the Sound file is loaded into.
 * @param audioManager the AudioManager to search.
 * @param filename The file name you are looking for.
 * @return The buffer ID where the sound is loaded into.
 */
ALuint AudioManager_findSound(AudioManager *audioManager, char *filename);

/**
 * Free's all the buffers stored inside of the AudioManager.
 * @param audioManager
 */
void AudioManager_free(AudioManager *audioManager);