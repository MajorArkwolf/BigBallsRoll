#include "audioManager.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Helper/stringHelper.h"

#define MAX_BUFF_SIZE 100

void AudioManager_init(AudioManager *audioManager) {
    audioManager->NumOfSounds = 0;
    audioManager->cwd = NULL;
}

void AudioManager_free(AudioManager *audioManager) {
    for (size_t i = 0; i < audioManager->NumOfSounds; ++i) {
        Sound_free(&audioManager->Sounds[i]);
    }
    audioManager->NumOfSounds = 0;
}

void AudioManager_loadSounds(AudioManager *audioManager, char *cwd) {
    assert(audioManager != NULL);
    char *fulldir = malloc(sizeof(char) * (strlen(cwd) + 30));
    strcpy(fulldir, cwd);
    strcat(fulldir, "res/Loader/soundloading.txt");
    FILE *fptr = fopen(fulldir, "r");
    assert(fptr != NULL);
    char buff[MAX_BUFF_SIZE];
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        removeNewLine(buff);
        if (buff[0] == '#') {
            continue;
        }
        char pathToSound[10000];
        strcpy(pathToSound, cwd);
        strcat(pathToSound, "res/Sound/");
        strcat(pathToSound, buff);
        strcpy(audioManager->Sounds[audioManager->NumOfSounds].Name, buff);
        audioManager->Sounds[audioManager->NumOfSounds].Buffer = Sound_loadSound(pathToSound);
        ++audioManager->NumOfSounds;
    }
    audioManager->cwd = cwd;
    fclose(fptr);
    free(fulldir);
}

bool AudioManager_findSound(AudioManager *audioManager, char *filename, ALuint *value) {
    if (value == NULL) {
        return false;
    }
    for (size_t i = 0; i < audioManager->NumOfSounds; ++i) {
        if (strcmp(audioManager->Sounds[i].Name, filename) == 0) {
            *value = i;
            return true;
        }
    }
    return false;
}

Sound* AudioManager_getSound(AudioManager *audioManager, ALuint soundID) {
    if (soundID >= 0 && soundID < audioManager->NumOfSounds) {
        return &audioManager->Sounds[soundID];
    }
    return NULL;
}
