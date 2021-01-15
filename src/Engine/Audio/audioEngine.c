#include "audioEngine.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void AudioEngine_init(AudioEngine *audioEngine) {
    audioEngine->Device = alcOpenDevice(NULL);
    if (audioEngine->Device == NULL) {
        printf("Failed to find default device.");
        assert(false);
    }
    audioEngine->Context = alcCreateContext(audioEngine->Device, NULL);
    if (audioEngine->Context == NULL) {
        printf("Failed to create a context.");
        assert(false);
    }
    if (!alcMakeContextCurrent(audioEngine->Context)) {
        printf("Failed to make context active.");
        assert(false);
    }

    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, 0, 0, 0.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    audioEngine->MaxNumSources = 0;
}

void AudioEngine_play(AudioEngine *audioEngine, ALuint source, Sound *sound) {
    if (source < audioEngine->MaxNumSources) {
        alSourcei(source, AL_BUFFER, sound->Buffer);
        alSourcePlay(source);
    }
}

void AudioEngine_stop_all(AudioEngine *audioEngine) {
    for (size_t i = 0; i < audioEngine->MaxNumSources; ++i) {
        alSourceStop(audioEngine->Sources[i]);
        alSourcei(audioEngine->Sources[i], AL_BUFFER, 0);
    }
}

void AudioEngine_listener(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity) {
    if (position != NULL) {
        alListener3f(AL_POSITION, position->X, position->Y, position->Z);
    }
    if (velocity != NULL) {
        alListener3f(AL_VELOCITY, velocity->X, velocity->Y, velocity->Z);
    }
}

ALuint AudioEngine_newSource(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity) {
    if (audioEngine->MaxNumSources == MAX_SOURCES) {
        return 0;
    }
    alGenSources((ALuint)1, &audioEngine->Sources[audioEngine->MaxNumSources]);// check for errors

    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_PITCH, 1);
// check for errors
    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_GAIN, 1);
// check for errors
    if (position != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources], AL_POSITION, position->X, position->Y, position->Z);
    }
// check for errors
    if (velocity != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources], AL_VELOCITY, velocity->X, velocity->Y,
                   velocity->Z);
    }
// check for errors
    //alSourcei(audioEngine->Sources[audioEngine->MaxNumSources], AL_LOOPING, AL_FALSE);


    return audioEngine->MaxNumSources++;
}

void AudioEngine_free(AudioEngine *audioEngine) {
    for (size_t i = 0; i < audioEngine->MaxNumSources; ++i) {
        alDeleteSources(1, &audioEngine->Sources[i]);
    }

    audioEngine->Device = alcGetContextsDevice(audioEngine->Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(audioEngine->Context);
    alcCloseDevice(audioEngine->Device);
}