#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <stdlib.h>
#include "sound.h"
#include "Math/vec3.h"
#include <stdbool.h>

#define MAX_SOURCES 10000

typedef struct AudioPresets {
    double MasterVolume;
} AudioPresets;

typedef struct AudioEngine {
    ALCdevice *Device;
    ALCcontext *Context;
    ALuint Sources[MAX_SOURCES];
    size_t MaxNumSources;
} AudioEngine;

/**
 * Initialise the audio engine.
 * @param audioEngine AudioEngine passed into to be configured for later use.
 */
void AudioEngine_init(AudioEngine *audioEngine);

/**
 * Play audio in relation to the source ID from a given source.
 * @param source ID to the object wanting to emit audio.
 * @param sound Sound object in relationship to an object.
 */
void AudioEngine_play(ALuint source, Sound *sound);

/**
 * Checks if the current source is playing.
 * @param source the source to check.
 * @return true if playing
 */
bool AudioEngine_isPlaying(ALuint source);

/**
 * Stop the current source if playing.
 * @param source the source to stop.
 */
void AudioEngine_stop(ALuint source);

/**
 * Pause the current source if playing.
 * @param source the source to pause.
 */
void AudioEngine_pause(ALuint source);

/**
 * This method is mainly for ensuring that all buffers are stopped so freeing
 * them doesnt cause issues.
 * @param audioEngine required as it stores all buffers.
 */
void AudioEngine_stop_all(AudioEngine *audioEngine);

/**
 * Updates the listener location for 3d sound.
 * @param position updates the position, can be null.
 * @param velocity updates the velocity, can be null.
 */
void AudioEngine_listenerLocation(Vec3 *position, Vec3 *velocity);

/**
 * Updates the orientation of the listener for 3d sound.
 * @param front front orientation, can not be null.
 * @param up up orientation, can not be null.
 */
void AudioEngine_listenerOrientation(Vec3 *front, Vec3 *up);

/**
 * Registers a new source for audio output.
 * @param audioEngine required to track the sources being registered.
 * @param position position of the audio source, can not be null.
 * @param velocity velocity of the audio source, can be null.
 * @return the buffer id, 0 if an error occurred.
 */
ALuint AudioEngine_newSource(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity);

/**
 * Updates the audio source location.
 * @param id ID to the source.
 * @param position update the position of the source, can be null.
 * @param velocity updates the velocity of the source, can be null.
 */
void AudioEngine_updateSource(ALuint id, Vec3 *position, Vec3 *velocity);

/**
 * Shuts the audio engine down.
 * @param audioEngine AudioEngine to shutdown.
 */
void AudioEngine_free(AudioEngine *audioEngine);

/**
 * Initialises the audio presets such as volume
 * @param ap structure to initialise
 */
void AudioEngine_AudioPresets_init(AudioPresets *ap);