#include "include/BigBalls/collisionBody.h"
#include <assert.h>

void CollisionBody_init(CollisionBody *collisionBody){
    collisionBody->colliderManager = calloc(1, sizeof(ColliderManager));
}

void CollisionBody_free(CollisionBody *collisionBody){
    assert(collisionBody != NULL);
    ColliderManager_free(collisionBody->colliderManager);
}
