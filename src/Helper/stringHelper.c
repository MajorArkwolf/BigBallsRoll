#include "stringHelper.h"
#include <string.h>

size_t getLastOccurrenceInString(char findThis, char* stringToCheck, size_t maxStringSize) {
    char *lastSlash = strrchr(stringToCheck, findThis);
    size_t indexValue = (lastSlash - stringToCheck) / sizeof(char);
    if (indexValue + 1 >= maxStringSize) {
        return 0;
    }
    return indexValue;
}

int replaceChar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while ((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

void removeNewLine(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}
