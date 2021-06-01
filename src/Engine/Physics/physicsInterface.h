#pragma once
#include "Engine/stateManager.h"

/**
 * Initialises the global DebugData object in physicsInterface.
 */
void PhysicsInterface_init();

void PhysicsInterface_update(double deltaTime);

/**
 * Frees the dynamic memory in the global DebugData object in physicsInterface.
 */
void PhysicsInterface_free();

/**
 * When toggled it draws all the collision bodies in wireframe.
 * @param physicsWorld the physics world whose collision bodies we want to draw.
 */
void PhysicsInterface_draw(PhysicsWorld *physicsWorld);

/**
 * Add force onto an existing body, this will sum all existing forces and will reset after resolution.
 * @param cb collision body to update
 * @param xForce force in the x direction
 * @param yForce force in the y direction
 * @param zForce force in the z direction
 */
void PhysicsInterface_addForce(CollisionBody *cb, float xForce, float yForce, float zForce);
