#include "stringPath.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "stringHelper.h"

char *getCurrentWorkingDirectory(char *path) {
    const size_t mallocSize = 1000;
    char *newStr = malloc(mallocSize * sizeof(char));
    if (newStr == NULL) {
        printf("malloc failed while getting current working directory.");
        assert(false);
    }
    strcpy(newStr, path);
    replaceChar(newStr, '\\', '/');
    size_t indexOf = getLastOccurrenceInString('/', newStr, mallocSize);
    newStr[indexOf + 1] = '\0';
    return newStr;
}

char *getFileTypeFromPath(char *path) {
    const int LEN = 4;
    char *ext = calloc(LEN, sizeof(char)); // file extension can be at most 4 characters
    if (ext == NULL) {
        printf("malloc failed while getting file type path.");
        assert(false);
    }
    size_t indexOf = getLastOccurrenceInString('.', path, strlen(path));
    strncpy(ext, path + indexOf + 1, LEN-1); // preserve null terminator
    return ext;
}
