#pragma once
#include "Engine/camera.h"

const float FRAMERATE = 1/60.0f;                     // ~60 FPS.
const float FRAMERATE_MILLIS = 1/60.0f * 1000;       // Millisecond version of framerate.
const float PHYSICS_MILLIS = 200;
float time = 0;
int width = 1920;
int height = 1080;
struct Camera camera;
