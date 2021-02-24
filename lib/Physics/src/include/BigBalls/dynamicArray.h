#pragma once
#include "stdlib.h"

#define SCALE_FACTOR 2

void DynamicArray_pushBackFloat(float *array, size_t size);

void DynamicArray_pushBackSizeT(size_t *array, size_t size);

void DynamicArray_insertFloat(float *array, size_t size);

void DynamicArray_insertSizeT(size_t *array, size_t size);
