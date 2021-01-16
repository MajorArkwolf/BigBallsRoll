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
    }
    if (velocity != NULL) {
        alListener3f(AL_VELOCITY, velocity->X, velocity->Y, velocity->Z);
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
    alGenSources((ALuint)1, &audioEngine->Sources[audioEngine->MaxNumSources]);// check for errors

    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_PITCH, 1);
// check for errors
    alSourcef(audioEngine->Sources[audioEngine->MaxNumSources], AL_GAIN, 1);
// check for errors
    if (position != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources],
                   AL_POSITION,
                   position->X,
                   position->Y,
                   position->Z);
    }
// check for errors
    if (velocity != NULL) {
        alSource3f(audioEngine->Sources[audioEngine->MaxNumSources],
                   AL_VELOCITY,
                   velocity->X,
                   velocity->Y,
                   velocity->Z);
    }
// check for errors
    //alSourcei(audioEngine->Sources[audioEngine->MaxNumSources], AL_LOOPING, AL_FALSE);

    ++audioEngine->MaxNumSources;
    return audioEngine->Sources[audioEngine->MaxNumSources - 1];
}

void AudioEngine_updateSource(ALuint id, Vec3 *position, Vec3 *velocity) {
    if (position != NULL) {
        alSource3f(id, AL_POSITION, position->X, position->Y, position->Z);
    }
// check for errors
    if (velocity != NULL) {
        alSource3f(id, AL_VELOCITY, velocity->X, velocity->Y,
                   velocity->Z);
    }
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