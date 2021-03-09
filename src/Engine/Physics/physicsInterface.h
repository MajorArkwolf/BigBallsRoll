#pragma once
#include "Engine/stateManager.h"

/**
 * Initialises the global DebugData object in physicsInterface.
 */
void PhysicsInterface_init();

void PhysicsInterface_update();

/**
 * Frees the dynamic memory in the global DebugData object in physicsInterface.
 */
void PhysicsInterface_free();

/**
 * When toggled it draws all the collision bodies in wireframe.
 * @param physicsWorld the physics world whose collision bodies we want to draw.
 */
void PhysicsInterface_draw(PhysicsWorld *physicsWorld);