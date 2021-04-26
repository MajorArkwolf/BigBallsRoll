#pragma once
#include "sound.h"
#include <stdlib.h>
#include <stdbool.h>

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
 * @param value this value is updated on successful search
 * @return true if sound is found or false if not.
 */
bool AudioManager_findSound(AudioManager *audioManager, char *filename, ALuint *value);

/**
 * Search the AudioManager and return the Sound pointer.
 * @param audioManager the AudioManager to search.
 * @param soundID the ID of the sound.
 * @return returns null if not found or a pointer to the sound.
 */
Sound* AudioManager_getSound(AudioManager *audioManager, ALuint soundID);

/**
 * Free's all the buffers stored inside of the AudioManager.
 * @param audioManager
 */
void AudioManager_free(AudioManager *audioManager);
