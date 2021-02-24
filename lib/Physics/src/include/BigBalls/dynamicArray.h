#pragma once
#include "stdlib.h"

#define SCALE_FACTOR 2
#define INITIAL_SIZE 16

// Float Array Object
typedef struct {
    float *array;
    size_t used; // The elements that are 'used', use this as the current max size, for loops or inserting, etc...
    size_t size; // The size of the array, not needed except for tracking if resize is needed
} FloatArray;

// SizeTArray Object
typedef struct {
    size_t *array;
    size_t used; // The elements that are 'used', use this as the current max size, for loops or inserting, etc...
    size_t size; // The size of the array, not needed except for tracking if resize is needed
} SizeTArray;

/**
 * Initialise a dynamic float array, must be called on a new FloatArray object.
 * @param array the FloatArray to initialise
 */
void DynamicArray_initFloat(FloatArray *array);

/**
 * Initialise a dynamic size_t array, must be called on a new SizeTArray object.
 * @param array the SizeTArray to initialise
 */
void DynamicArray_initSizeT(SizeTArray *array);

/**
 * Pushes a float variable to the back of the Array. If the array is full the array
 * is resized to SCALE_FACTOR its current size using realloc.
 * @param array the array to place the float variable in
 * @param var the float variable to place in the array
 */
void DynamicArray_pushBackFloat(FloatArray *array, float var);

/**
 * Pushes a size_t variable to the back of the Array. If the array is full the array
 * is resized to SCALE_FACTOR its current size using realloc.
 * @param array the array to place the size_t variable in
 * @param var the float variable to place in the array
 */
void DynamicArray_pushBackSizeT(SizeTArray *array, size_t var);

/**
 * Inserts a float into the float array. Can only insert up to the used value in the array, to ensure
 * the var isn't overwritten by the pushback function later.
 * @param array the array to insert into
 * @param index the index of the array to insert the var
 * @param var the float variable to insert
 */
void DynamicArray_insertFloat(FloatArray *array, size_t index, float var);

/**
 * Inserts a size_t into the size_t array. Can only insert up to the used value in the array, to ensure
 * the var isn't overwritten by the pushback function later.
 * @param array the array to insert into
 * @param index the index of the array to insert the var
 * @param var the size_t variable to insert
 */
void DynamicArray_insertSizeT(SizeTArray *array, size_t index, size_t var);

/**
 * Frees the contents of the FloatArray, and not the array pointer itself. This is so the array can be erased between frames.
 * Can be used to free the object before freeing the array pointer.
 * @param array the FloatArray with the content to free
 */
void DynamicArray_eraseFloat(FloatArray *array);

/**
 * Frees the contents of the SizeTArray, and not the array pointer itself. This is so the array can be erased between frames.
 * Can be used to free the object before freeing the array pointer.
 * @param array the SizeTArray with the content to free
 */
void DynamicArray_eraseSizeT(SizeTArray *array);
