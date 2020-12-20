#pragma once
#include <stdio.h>

//The max number of tokens
#define MAX_NUM_TOKENS 1024

/**
 * Turns a list of characters into seperated tokens based on tokenSeperators
 * @param inputLine The line of characters to read from and to turn into tokens
 * @param token The already allocated array to place tokenised words into, should have MAX_NUM_TOKENS space allocated
 * @param separators A list of characters to search through to to separate tokens by
 * @return The number of tokens put into the tokens array, or -1 if it has exceeded MAX_NUM_TOKENS
 */
int Tokenise(char *inputLine, char *token[], char* separators);


char * GetPathFromTokens( char** tokens, int numTokens, int startToken);

char *GetCurrentWorkingDirectory(char* path);