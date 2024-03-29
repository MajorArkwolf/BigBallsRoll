#pragma once
#include "stdlib.h"

#define SCALE_FACTOR 2
#define INITIAL_CAPACITY 16

// Float Array Object
typedef struct {
    float *array;
    size_t size; // The size of the array
    size_t capacity; // The capacity of the array, not needed except for tracking if resize is needed
} FloatArray;

// SizeTArray Object
typedef struct {
    size_t *array;
    size_t size; // The size of the array
    size_t capacity; // The capacity of the array, not needed except for tracking if resize is needed
} SizeTArray;

/**
 * Initialise a dynamic float array, must be called on a new FloatArray object.
 * @param obj the FloatArray to initialise
 */
void DynamicArray_initFloat(FloatArray *obj);

/**
 * Initialise a dynamic size_t array, must be called on a new SizeTArray object.
 * @param obj the SizeTArray to initialise
 */
void DynamicArray_initSizeT(SizeTArray *obj);

/**
 * Pushes a float variable to the back of the Array. If the array is full the array
 * is resized to SCALE_FACTOR its current capacity using realloc.
 * @param obj the obj to place the float variable in
 * @param var the float variable to place in the array
 */
void DynamicArray_pushBackFloat(FloatArray *obj, float var);

/**
 * Pushes a size_t variable to the back of the Array. If the array is full the array
 * is resized to SCALE_FACTOR its current capacity using realloc.
 * @param obj the obj to place the size_t variable in
 * @param var the float variable to place in the array
 */
void DynamicArray_pushBackSizeT(SizeTArray *obj, size_t var);

/**
 * Inserts a float into the float array. Can only insert up to the size of the array, to ensure
 * the var isn't overwritten by the pushback function later.
 * @param obj the obj to insert into
 * @param index the index of the array to insert the var
 * @param var the float variable to insert
 */
void DynamicArray_insertFloat(FloatArray *obj, size_t index, float var);

/**
 * Inserts a size_t into the size_t array. Can only insert up to the size of the array, to ensure
 * the var isn't overwritten by the pushback function later.
 * @param obj the obj to insert into
 * @param index the index of the array to insert the var
 * @param var the size_t variable to insert
 */
void DynamicArray_insertSizeT(SizeTArray *obj, size_t index, size_t var);

/**
 * Frees the contents of the FloatArray, and not the array pointer itself. This is so the array can be erased between frames.
 * @param obj the FloatArray with the content to free
 */
void DynamicArray_eraseFloat(FloatArray *obj);

/**
 * Frees the contents of the SizeTArray, and not the array pointer itself. This is so the array can be erased between frames.
 * @param obj the SizeTArray with the content to free
 */
void DynamicArray_eraseSizeT(SizeTArray *obj);

/**
 * Frees the contents of the FloatArray.
 * @param obj the object to free
 */
void DynamicArray_freeFloat(FloatArray *obj);

/**
 * Frees the contents of the SizeTArray.
 * @param obj the object to free
 */
void DynamicArray_freeSizeT(SizeTArray *obj);
