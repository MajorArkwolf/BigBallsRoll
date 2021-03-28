#include "stringPath.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stringHelper.h"

char *getCurrentWorkingDirectory(char *path) {
    size_t mallocSize = strlen(path) * sizeof(char) + 1;
    char *newStr = malloc(mallocSize);
    if (newStr != NULL) {
        printf("malloc failed while getting current working directory.");
        assert(false);
        strcpy(newStr, path);
        replaceChar(newStr, '\\', '/');
        size_t indexOf = getLastOccurrenceInString('/', newStr);
        newStr[indexOf + 1] = '\0';
        return newStr;
    }
    assert(false);
    return NULL;
}

char *getFileTypeFromPath(char *path) {
    const int LEN = 4;
    char *ext = calloc(LEN, sizeof(char)); // file extension can be at most 4 characters
    if (ext == NULL) {
        printf("malloc failed while getting file type path.");
        assert(false);
    }
    size_t indexOf = getLastOccurrenceInString('.', path);
    strncpy(ext, path + indexOf + 1, LEN-1); // preserve null terminator
    return ext;
}
