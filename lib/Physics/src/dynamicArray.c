#include "include/BigBalls/dynamicArray.h"
#include "assert.h"

void DynamicArray_initFloat(FloatArray *array) {
    assert(array != NULL);
    array->array = calloc(INITIAL_SIZE, sizeof(float));
    array->size = INITIAL_SIZE;
    array->used = 0;
}

void DynamicArray_initSizeT(SizeTArray *array) {
    assert(array != NULL);
    array->array = calloc(INITIAL_SIZE, sizeof(size_t));
    array->size = INITIAL_SIZE;
    array->used = 0;
}

void DynamicArray_pushBackFloat(FloatArray *array, float var) {
    assert(array != NULL && array->array != NULL);
    if (array->size == array->used) {
        array->size *= SCALE_FACTOR;
        array->array = realloc(array->array, array->size * sizeof(float));
    }
    array->array[array->used++] = var;
}

void DynamicArray_pushBackSizeT(SizeTArray *array, size_t var) {
    assert(array != NULL && array->array != NULL);
    if (array->size == array->used) {
        array->size *= SCALE_FACTOR;
        array->array = realloc(array->array, array->size * sizeof(size_t));
    }
    array->array[array->used++] = var;
}

void DynamicArray_insertFloat(FloatArray *array, size_t index, float var) {
    assert(array != NULL && array->used >= index && array->array != NULL);
    array->array[index] = var;
}

void DynamicArray_insertSizeT(SizeTArray *array, size_t index, size_t var) {
    assert(array != NULL && array->used >= index && array->array != NULL);
    array->array[index] = var;
}

void DynamicArray_eraseFloat(FloatArray *array) {
    assert(array != NULL && array->array != NULL);
    free(array->array);
    array->array = calloc(INITIAL_SIZE, sizeof(float));
    array->size = INITIAL_SIZE;
    array->used = 0;
}

void DynamicArray_eraseSizeT(SizeTArray *array) {
    assert(array != NULL && array->array != NULL);
    free(array->array);
    array->array = calloc(INITIAL_SIZE, sizeof(float));
    array->size = INITIAL_SIZE;
    array->used = 0;
}

void DynamicArray_freeFloat(FloatArray *array) {
    assert(array != NULL && array->array != NULL);
    free(array->array);
    array->size = 0;
    array->used = 0;
}

void DynamicArray_freeSizeT(SizeTArray *array) {
    assert(array != NULL && array->array != NULL);
    free(array->array);
    array->size = 0;
    array->used = 0;
}
