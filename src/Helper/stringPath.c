#include "stringPath.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "stringHelper.h"

char *getCurrentWorkingDirectory(char *path) {
    const size_t mallocSize = 1000;
    char *newStr = malloc(mallocSize * sizeof(char));
    if (newStr == NULL) {
        assert(false);
    }
    strcpy(newStr, path);
    replaceChar(newStr, '\\', '/');
    size_t indexOf = getLastOccurrenceInString('/', newStr, mallocSize);
    newStr[indexOf + 1] = '\0';
    return newStr;
}

char *getFileTypeFromPath(char *path) {
    char *ext = malloc(4 * sizeof(char));
    if (ext == NULL) {
        assert(false);
    }
    size_t indexOf = getLastOccurrenceInString('.', path, strlen(path));
    strncpy(ext, path + indexOf + 1, strlen(path));
    return ext;
}
