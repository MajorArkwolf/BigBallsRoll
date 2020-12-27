#include "token.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


int tokenise(char *inputLine, char **token, char *separators) {
    char *readToken = strtok(inputLine, separators);
    int count = 0;

    token[count] = readToken;
    while (readToken != NULL) {
        ++count;
        if (count >= MAX_NUM_TOKENS) {
            return -1;
        }
        readToken = strtok(NULL, separators);
        token[count] = readToken;
    }
    return count;
}

char *getPathFromTokens(char **tokens, int numTokens, int startToken) {
    char *output = (char *) calloc(FILENAME_MAX, sizeof(char));
    if (numTokens > startToken) {
        for (int i = startToken; i < numTokens; ++i) {
            strcat(output, tokens[i]);
            if (i + 1 != numTokens) {
                strcat(output, " ");
            }
        }
    }
    return output;
}

int ReplaceChar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while ((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}
