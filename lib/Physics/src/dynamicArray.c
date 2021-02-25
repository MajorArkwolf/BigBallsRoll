#include "include/BigBalls/dynamicArray.h"
#include "assert.h"

void DynamicArray_initFloat(FloatArray *obj) {
    assert(obj != NULL);
    obj->array = calloc(INITIAL_SIZE, sizeof(float));
    obj->size = INITIAL_SIZE;
    obj->used = 0;
}

void DynamicArray_initSizeT(SizeTArray *obj) {
    assert(obj != NULL);
    obj->array = calloc(INITIAL_SIZE, sizeof(size_t));
    obj->size = INITIAL_SIZE;
    obj->used = 0;
}

void DynamicArray_pushBackFloat(FloatArray *obj, float var) {
    assert(obj != NULL && obj->array != NULL);
    if (obj->size == obj->used) {
        obj->size *= SCALE_FACTOR;
        obj->array = realloc(obj->array, obj->size * sizeof(float));
    }
    obj->array[obj->used++] = var;
}

void DynamicArray_pushBackSizeT(SizeTArray *obj, size_t var) {
    assert(obj != NULL && obj->array != NULL);
    if (obj->size == obj->used) {
        obj->size *= SCALE_FACTOR;
        obj->array = realloc(obj->array, obj->size * sizeof(size_t));
    }
    obj->array[obj->used++] = var;
}

void DynamicArray_insertFloat(FloatArray *obj, size_t index, float var) {
    assert(obj != NULL && obj->used >= index && obj->array != NULL);
    obj->array[index] = var;
}

void DynamicArray_insertSizeT(SizeTArray *obj, size_t index, size_t var) {
    assert(obj != NULL && obj->used >= index && obj->array != NULL);
    obj->array[index] = var;
}

void DynamicArray_eraseFloat(FloatArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->array = calloc(INITIAL_SIZE, sizeof(float));
    obj->size = INITIAL_SIZE;
    obj->used = 0;
}

void DynamicArray_eraseSizeT(SizeTArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->array = calloc(INITIAL_SIZE, sizeof(size_t));
    obj->size = INITIAL_SIZE;
    obj->used = 0;
}

void DynamicArray_freeFloat(FloatArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->size = 0;
    obj->used = 0;
}

void DynamicArray_freeSizeT(SizeTArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->size = 0;
    obj->used = 0;
}

