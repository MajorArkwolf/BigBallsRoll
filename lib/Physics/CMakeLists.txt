cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME BigBallPhysics)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C)

set(PHYSICS_HEADERS
    "src/include/BigBalls/physicsEngine.h"
    "src/include/BigBalls/collisionBody.h"
    "src/include/BigBalls/physicsWorld.h"
    "src/include/BigBalls/boxCollider.h"
    "src/include/BigBalls/sphereCollider.h"
    "src/include/BigBalls/dynamicArray.h"
    "src/include/BigBalls/physicsDebug.h")

set(PHYSICS_SOURCES
    "src/physicsEngine.c"
    "src/collisionBody.c"
    "src/physicsWorld.c"
    "src/boxCollider.c"
    "src/sphereCollider.c"
    "src/dynamicArray.c"
    "src/physicsDebug.c")

add_library(${PROJECT_NAME} ${PHYSICS_HEADERS} ${PHYSICS_SOURCES})
add_library(BigBalls::Physics ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE src/)
target_include_directories(${PROJECT_NAME} INTERFACE src/include/)
