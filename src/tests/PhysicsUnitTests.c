#include <unity.h>
#include "PhysicsUnitTests.h"
#include "BigBalls/physicsEngine.h"

void testIdentity44(){
    Matrix44 sus = identity44();
    Matrix44 target = {.elem[0] = {1, 0, 0, 0},
        .elem[1] = {0, 1, 0, 0},
        .elem[2] = {0, 0, 1, 0},
        .elem[3] = {0, 0, 0, 1}};
    TEST_ASSERT(compareMatrix44(sus, target) == 1);
}

void testMatrixMultiplication44_44(){
    Matrix44 a = {.elem[0] = {5, 2, 6, 1},
        .elem[1] = {0, 6, 2, 0},
        .elem[2] = {3, 8, 1, 4},
        .elem[3] = {1, 8 ,5, 6}};
    Matrix44 b = {.elem[0] = {7, 5, 8, 0},
        .elem[1] = {1, 8, 2, 6},
        .elem[2] = {9, 4, 3, 8},
        .elem[3] = {5, 3, 7, 9}};
    Matrix44 sus = matrixMultiplication44_44(a, b);
    Matrix44 target = {.elem[0] = {96, 68, 69, 69},
        .elem[1] = {24, 56, 18, 52},
        .elem[2] = {58, 95, 71, 92},
        .elem[3] = {90, 107, 81, 142}};
    TEST_ASSERT(compareMatrix44(sus, target) == 1);
}

void testMatrixMultiplication44_41(){
    Matrix44 a = {.elem[0] = {5, 45, -3, 4},
        .elem[1] = {3, -2, 11, 9},
        .elem[2] = {2, 31, 6, 22},
        .elem[3] = {6, -5 ,-9, 7}};
    Matrix41 b = {2, -3, 4, 5};
    Matrix41 sus = matrixMultiplication44_41(a, b);
    Matrix41 target = {-117, 101, 45, 26};
    TEST_ASSERT(compareMatrix41(sus, target) == 1);
}

void testIdenticalCollision(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody1, collider1);
    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider1->xLen = 10.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody2, collider2);
    for(int i = 0; i <= 9; ++i){
        CollisionBody_translate(collisionBody2, 1, 0, 0);
    }
    bool colliding = testAABBCollision(collisionBody1, collisionBody2);
    TEST_ASSERT(colliding == 1);
}

void testNonCollision(){
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
    collider1->xOffset = 0;
    collider1->yOffset = 0;
    collider1->zOffset = 0;
    collider1->xLen = 1.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody1, collider1);
    // create CollisionBody for object
    CollisionBody* collisionBody2 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody2);
    // create collider
    BoxCollider *collider2 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider2);
    collider2->xOffset = 1.1f;
    collider2->yOffset = 1.1f;
    collider2->zOffset = 1.1f;
    collider2->xLen = 1.f;
    collider2->yLen = 1.f;
    collider2->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody2, collider2);
    TEST_ASSERT_FALSE(testAABBCollision(collisionBody1, collisionBody2));
}

void testRotationX(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 90.f, 0.f, 0.f);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy1, -3.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBx2, 1.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy2, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz2, 2.f, 0.0001f));
}

void testRotationY(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 0.f, 90.f, 0.f);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz1, -1.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBx2, 3.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy2, 2.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz2, 0.f, 0.0001f));
}

void testRotationZ(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 0.f, 0.f, 90.f);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, -2.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBx2, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy2, 1.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz2, 3.f, 0.0001f));
}

void testRotationOverflow(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xRot = 360;
    collider->yRot = 360;
    collider->zRot = 360;
    CollisionBody_addBoxCollider(collisionBody, collider);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->BoxColliders[0]->xRot == 0, 0, 0.0001) &&
                     fTolerance(collisionBody->BoxColliders[0]->yRot == 0, 0, 0.0001) &&
                     fTolerance(collisionBody->BoxColliders[0]->zRot == 0, 0, 0.0001));
    CollisionBody_setRot(collisionBody, 360.f, 360.f, 360.f);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->xRot, 0.f, 0.0001f) &&
                     fTolerance(collisionBody->yRot, 0.f, 0.0001f) &&
                     fTolerance(collisionBody->zRot, 0.f, 0.0001f));
}

void testColliderRotation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xRot = 45;
    collider->yRot = 45;
    collider->zRot = 45;
    CollisionBody_addBoxCollider(collisionBody, collider);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, -0.3f, 0.1f) &&
                     fTolerance(collisionBody->AABBy1, -0.4f, 0.1f) &&
                     fTolerance(collisionBody->AABBz1, -0.7f, 0.1f) &&
                     fTolerance(collisionBody->AABBx2, 3.f, 0.1f) &&
                     fTolerance(collisionBody->AABBy2, 2.2f, 0.1f) &&
                     fTolerance(collisionBody->AABBz2, 2.5f, 0.1f));
}

void testCollisionBodyRotation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_rotate(collisionBody, 45, 45, 45);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, -0.3f, 0.1f) &&
                     fTolerance(collisionBody->AABBy1, -0.4f, 0.1f) &&
                     fTolerance(collisionBody->AABBz1, -0.7f, 0.1f) &&
                     fTolerance(collisionBody->AABBx2, 3.f, 0.1f) &&
                     fTolerance(collisionBody->AABBy2, 2.2f, 0.1f) &&
                     fTolerance(collisionBody->AABBz2, 2.5f, 0.1f));
}

void testCombinedRotation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 10.f;
    collider->yLen = 1.f;
    collider->zOffset = -1;
    collider->zLen = 1.f;
    collider->xRot = 45;
    collider->yRot = 45;
    collider->zRot = 45;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_rotate(collisionBody, -45, -45, -45);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 0.f, 1.f) &&
                     fTolerance(collisionBody->AABBy1, -8.f, 1.f) &&
                     fTolerance(collisionBody->AABBz1, -4.f, 1.f) &&
                     fTolerance(collisionBody->AABBx2, 6.f, 1.f) &&
                     fTolerance(collisionBody->AABBy2, 0.6f, 1.f) &&
                     fTolerance(collisionBody->AABBz2, 0.f, 1.f));
}

void testRotation(){
    RUN_TEST(testRotationX);
    RUN_TEST(testRotationY);
    RUN_TEST(testRotationZ);
    RUN_TEST(testRotationOverflow);
    RUN_TEST(testColliderRotation);
    RUN_TEST(testCollisionBodyRotation);
    RUN_TEST(testCombinedRotation);
}

void testColliderTranslation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xOffset = 5;
    collider->yOffset = 5;
    collider->zOffset = 5;
    CollisionBody_addBoxCollider(collisionBody, collider);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBx2, 6.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy2, 7.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz2, 8.f, 0.0001f));
}

void testCollisionBodyTranslation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_translate(collisionBody, 5, 5, 5);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz1, 5.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBx2, 6.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy2, 7.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz2, 8.f, 0.0001f));
};

void testStackedTranslation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xOffset = 5;
    collider->yOffset = 5;
    collider->zOffset = 5;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_translate(collisionBody, 5, 5, 5);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 10.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy1, 10.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz1, 10.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBx2, 11.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBy2, 12.f, 0.0001f) &&
                     fTolerance(collisionBody->AABBz2, 13.f, 0.0001f));
}

void testTranslation(){
    RUN_TEST(testColliderTranslation);
    RUN_TEST(testCollisionBodyTranslation);
    RUN_TEST(testStackedTranslation);
}

// check that all transformations stack together correctly
void testCombinedTransformation(){
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xOffset = 5;
    collider->yOffset = 5;
    collider->zOffset = 5;
    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_translate(collisionBody, 5, 5, 5);
    CollisionBody_rotate(collisionBody, 45, 45, 45);
    TEST_ASSERT_TRUE(fTolerance(collisionBody->AABBx1, 10.7f, 0.1f) &&
                     fTolerance(collisionBody->AABBy1, 10.6f, 0.1f) &&
                     fTolerance(collisionBody->AABBz1, 5.7f, 0.1f) &&
                     fTolerance(collisionBody->AABBx2, 14.1f, 0.1f) &&
                     fTolerance(collisionBody->AABBy2, 13.2f, 0.1f) &&
                     fTolerance(collisionBody->AABBz2, 8.9f, 0.1f));
}

void test_Physics(){
    RUN_TEST(testIdentity44);
    RUN_TEST(testMatrixMultiplication44_44);
    RUN_TEST(testMatrixMultiplication44_41);
    RUN_TEST(testIdenticalCollision);
    RUN_TEST(testNonCollision);
    RUN_TEST(testRotation);
    RUN_TEST(testTranslation);
    RUN_TEST(testCombinedTransformation);
}