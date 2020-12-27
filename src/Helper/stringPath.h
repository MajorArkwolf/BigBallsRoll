#pragma once

/**
 * Extract the working directory from a full path (removes file formats)
 * @param path full path to the working directory.
 * @return returns an allocated string with the working directory.
 */
char *getCurrentWorkingDirectory(char *path);

/**
 * Extracts the file type from a full path, for example .exe or .obj.
 * @param path the full path to be extracted from.
 * @return the result minus the .
 */
char *getFileTypeFromPath(char *path);
