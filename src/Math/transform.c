#include "transform.h"

Transform Transformation_construct() {
    Transform newTran;
    newTran.Position = Vec3_construct();
    newTran.Rotation = Vec3_construct();
    newTran.Scale.X = 1.0f;
    newTran.Scale.Y = 1.0f;
    newTran.Scale.Z = 1.0f;
    return newTran;
}
