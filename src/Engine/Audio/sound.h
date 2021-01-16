#pragma once
#include <AL/al.h>

typedef struct Sound {
    char Name[1000];
    ALuint Buffer;
} Sound;

/**
 * Initialises a Sound object, This function will NOT load a sound object, simply prep it for future use.
 * @param name the filename of the sound you wish to load in the future.
 * @return an initialised sound object.
 */
Sound Sound_init(char *name);

/**
 * Deletes the OpenAL buffer if it exists.
 * @param sound
 */
void Sound_free(Sound *sound);

/**
 * Load a sound from the res/Sound/ file into an OpenAL buffer.
 * @param filename The location of the file to load.
 * @return The ID of which buffer contains the sound file.
 */
ALuint Sound_loadSound(const char *filename);