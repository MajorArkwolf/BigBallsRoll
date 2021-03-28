#include "audioEngine.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Engine/engine.h"

/**
 * 1) Identify the error code.
 * 2) Return the error as a string.
 */
static void getErrorString(int err) {
    if (err > 0) {
        switch (err) {
            case ALC_NO_ERROR:
                printf("AL_NO_ERROR");
            case ALC_INVALID_DEVICE:
                printf("ALC_INVALID_DEVICE");
            case ALC_INVALID_CONTEXT:
                printf("ALC_INVALID_CONTEXT");
            case ALC_INVALID_ENUM:
                printf("ALC_INVALID_ENUM");
            case ALC_INVALID_VALUE:
                printf("ALC_INVALID_VALUE");
            case ALC_OUT_OF_MEMORY:
                printf("ALC_OUT_OF_MEMORY");
            default:
                printf("no such error code");
        }
        assert(false);
    }
}

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
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, listenerOri);

    audioEngine->MaxNumSources = 0;
}

void AudioEngine_play(ALuint source, Sound *sound) {
    alSourcei(source, AL_BUFFER, sound->Buffer);
    alSourcePlay(source);
}

bool AudioEngine_isPlaying(ALuint source) {
    ALenum state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

void AudioEngine_stop(ALuint source) {
    alSourceStop(source);
}

void AudioEngine_pause(ALuint source) {
    alSourcePause(source);
}

void AudioEngine_stop_all(AudioEngine *audioEngine) {
    for (size_t i = 0; i < audioEngine->MaxNumSources; ++i) {
        alSourceStop(audioEngine->Sources[i]);
        alSourcei(audioEngine->Sources[i], AL_BUFFER, 0);
    }
}

void AudioEngine_listenerLocation(Vec3 *position, Vec3 *velocity) {
    if (position != NULL) {
        alListener3f(AL_POSITION, position->X, position->Y, position->Z);
        getErrorString(alGetError());
    }
    if (velocity != NULL) {
        alListener3f(AL_VELOCITY, velocity->X, velocity->Y, velocity->Z);
        getErrorString(alGetError());
    }
}

void AudioEngine_listenerOrientation(Vec3 *front, Vec3 *up) {
    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    listenerOri[0] = front->X;
    listenerOri[1] = front->Y;
    listenerOri[2] = front->Z;
    listenerOri[0] = up->X;
    listenerOri[1] = up->Y;
    listenerOri[2] = up->Z;
    alListenerfv(AL_ORIENTATION, listenerOri);
}

ALuint AudioEngine_newSource(AudioEngine *audioEngine, Vec3 *position, Vec3 *velocity) {
    if (audioEngine->MaxNumSources == MAX_SOURCES) {
        return 0;
    }
    AudioPresets *ap = &engine.audioPresets;
    alGenSources((ALuint)1, &audioEngine->Sources[audioEngine->MaxNumSources]);// check for errors
    getErrorString(alGetError());
    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_PITCH, 1);
    getErrorString(alGetError());
    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_GAIN, ap->MasterVolume);
    getErrorString(alGetError());
    if (position != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources],
                   AL_POSITION,
                   position->X,
                   position->Y,
                   position->Z);
    }
    getErrorString(alGetError());
    if (velocity != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources],
                   AL_VELOCITY,
                   velocity->X,
                   velocity->Y,
                   velocity->Z);
    }
    ++audioEngine->MaxNumSources;
    return audioEngine->Sources[audioEngine->MaxNumSources - 1];
}

void AudioEngine_updateSource(ALuint id, Vec3 *position, Vec3 *velocity) {
    if (position != NULL) {
        alSource3f(id, AL_POSITION, position->X, position->Y, position->Z);
    }
    getErrorString(alGetError());
    if (velocity != NULL) {
        alSource3f(id, AL_VELOCITY, velocity->X, velocity->Y,
                   velocity->Z);
    }
    getErrorString(alGetError());
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

void AudioEngine_AudioPresets_init(AudioPresets *ap) {
    ap->MasterVolume = 100.0;
}
