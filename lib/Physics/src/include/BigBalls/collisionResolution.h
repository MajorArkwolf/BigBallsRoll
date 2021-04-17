#pragma once
#include "physicsMathsCommon.h"

/**
 * Pass in a series of collisions in a array then let the algorithm resolve it.
 * @param collisionArray An array of 1:N collisions that need to be resolved.
 * @param numOfCollisions How many collisions exist in the array.
 */
void collisionResolution(Collision* collisionArray, size_t numOfCollisions);