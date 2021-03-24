#include "include/BigBalls/dynamicArray.h"
#include "assert.h"

void DynamicArray_initFloat(FloatArray *obj) {
    assert(obj != NULL);
    obj->array = calloc(INITIAL_CAPACITY, sizeof(float));
    obj->size = 0;
    obj->capacity = INITIAL_CAPACITY;
}

void DynamicArray_initSizeT(SizeTArray *obj) {
    assert(obj != NULL);
    obj->array = calloc(INITIAL_CAPACITY, sizeof(size_t));
    obj->size = 0;
    obj->capacity = INITIAL_CAPACITY;
}

void DynamicArray_pushBackFloat(FloatArray *obj, float var) {
    assert(obj != NULL && obj->array != NULL);
    if (obj->size == obj->capacity) {
        obj->capacity *= SCALE_FACTOR;
        obj->array = realloc(obj->array, obj->capacity * sizeof(float));
    }
    obj->array[obj->size++] = var;
}

void DynamicArray_pushBackSizeT(SizeTArray *obj, size_t var) {
    assert(obj != NULL && obj->array != NULL);
    if (obj->size == obj->capacity) {
        obj->capacity *= SCALE_FACTOR;
        obj->array = realloc(obj->array, obj->capacity * sizeof(size_t));
    }
    obj->array[obj->size++] = var;
}

void DynamicArray_insertFloat(FloatArray *obj, size_t index, float var) {
    assert(obj != NULL && obj->size >= index && obj->array != NULL);
    obj->array[index] = var;
}

void DynamicArray_insertSizeT(SizeTArray *obj, size_t index, size_t var) {
    assert(obj != NULL && obj->size >= index && obj->array != NULL);
    obj->array[index] = var;
}

void DynamicArray_eraseFloat(FloatArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->array = calloc(INITIAL_CAPACITY, sizeof(float));
    obj->size = 0;
    obj->capacity = INITIAL_CAPACITY;
}

void DynamicArray_eraseSizeT(SizeTArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->array = calloc(INITIAL_CAPACITY, sizeof(size_t));
    obj->size = 0;
    obj->capacity = INITIAL_CAPACITY;
}

void DynamicArray_freeFloat(FloatArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->size = 0;
    obj->capacity = 0;
}

void DynamicArray_freeSizeT(SizeTArray *obj) {
    assert(obj != NULL && obj->array != NULL);
    free(obj->array);
    obj->size = 0;
    obj->capacity = 0;
}

