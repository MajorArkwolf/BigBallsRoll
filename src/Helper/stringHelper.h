#pragma once
#include <stdlib.h>

/**
 * Get the last occurrence of a char in a string.
 * @param findThis the character to search for.
 * @param stringToCheck the string to check.
 * @return the location of the last character found in the string else return 0
 */
size_t getLastOccurrenceInString(char findThis, char* stringToCheck);

/**
 * Replace all characters in a string, useful for replacing backslashes with forward slashes.
 * @param str string to alter
 * @param orig the character to replace
 * @param rep the character replacing
 * @return how many replaces occured
 */
int replaceChar(char *str, char orig, char rep);

/**
 * Remove new line from string
 * @param str string to alter
 */
void removeNewLine(char *str);
