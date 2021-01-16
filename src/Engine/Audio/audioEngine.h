#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <stdlib.h>
#include "sound.h"
#include "Math/vec3.h"

#define MAX_SOURCES 10000

typedef struct AudioEngine {
    ALCdevice *Device;
    ALCcontext *Context;
    ALuint Sources[MAX_SOURCES];
    size_t MaxNumSources;
} AudioEngine;

void AudioEngine_init(AudioEngine *audioEngine);

void AudioEngine_play(AudioEngine *audioEngine, ALuint source, Sound *sound);

void AudioEngine_stop_all(AudioEngine *audioEngine);

void AudioEngine_listenerLocation(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity);

void AudioEngine_listenerOrientation(AudioEngine *audioEngine, Vec3 *front, Vec3 *up);

ALuint AudioEngine_newSource(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity);

void AudioEngine_updateSource(AudioEngine *audioEngine, ALuint id ,Vec3 *position, Vec3 *velocity);

void AudioEngine_free(AudioEngine *audioEngine);