#include "extraMath.h"
#include <math.h>
#define m_PI 3.142f

float ExtraMath_toRadians(float val) {
    return (m_PI / 180.0f) * val;
}

float ExtraMath_toDegrees(float val) {
    return val * (180.0f / m_PI);
}
