#pragma once
#include <AL/al.h>

typedef struct Sound {
    char Name[1000];
    ALuint Buffer;
} Sound;

Sound Sound_init(char *name);

void Sound_free(Sound *sound);

ALuint Sound_loadSound(const char *filename);