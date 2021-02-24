#pragma once
#include "stdlib.h"

#define SCALE_FACTOR 2

typedef struct {
    float *array;
    size_t used;
    size_t size;
} FloatArray;

typedef struct {
    size_t *array;
    size_t used;
    size_t size;
} SizeTArray;

void DynamicArray_initFloat(FloatArray *array);

void DynamicArray_initSizeT(SizeTArray *array);

void DynamicArray_pushBackFloat(FloatArray *array, float var);

void DynamicArray_pushBackSizeT(SizeTArray *array, size_t var);

void DynamicArray_insertFloat(FloatArray *array, size_t index, float var);

void DynamicArray_insertSizeT(SizeTArray *array, size_t index, size_t var);
