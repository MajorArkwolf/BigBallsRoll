cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME BigBallPhysics)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES C)

set(PHYSICS_HEADERS
    "include/BigBalls/physicsEngine.h"
)

set(PHYSICS_SOURCES
    "src/physicsEngine.c"
)

add_library(${PROJECT_NAME} ${PHYSICS_HEADERS} ${PHYSICS_SOURCES})
add_library(BigBall::Physics ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE src/)
target_include_directories(${PROJECT_NAME} INTERFACE include/)