#pragma once
#include <AL/al.h>
#include <AL/alc.h>
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

void AudioEngine_listener(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity);

ALuint AudioEngine_newSource(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity);

void AudioEngine_free(AudioEngine *audioEngine);