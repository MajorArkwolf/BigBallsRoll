#include "unitTestEntry.h"
#define CESTER_NO_MAIN
#include <exotic/cester.h>
#include <math.h>
#include <stdbool.h>
#include "BigBalls/physicsWorld.h"
#include "BigBalls/collisionBody.h"
#include "BigBalls/mathsCommon.h"


// For more information on how to add and do unit tests view these links.
// https://exoticlibraries.github.io/libcester/docs/manual_test_registration.html


CESTER_TEST(test_one, inst,
        cester_assert_equal(NULL, ((void*)0));
)

/*
CESTER_TEST(TestIdentity44, TestPhysics,
    Matrix44 sus = identity44();
    Matrix44 target = {.elem[0] = {1, 0, 0, 0},
                       .elem[1] = {0, 1, 0, 0},
                       .elem[2] = {0, 0, 1, 0},
                       .elem[3] = {0, 0, 0, 1}};
    cester_assert_cmp(compareMatrix44(sus, target),==, 1);
)

CESTER_TEST(TestMatrixMultiplication44_44, TestPhysics,
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
    cester_assert_cmp(compareMatrix44(sus, target), ==, 1);
)

CESTER_TEST(TestMatrixMultiplication44_41, TestPhysics,
    Matrix44 a = {.elem[0] = {5, 45, -3, 4},
                  .elem[1] = {3, -2, 11, 9},
                  .elem[2] = {2, 31, 6, 22},
                  .elem[3] = {6, -5 ,-9, 7}};
    Matrix41 b = {2, -3, 4, 5};
    Matrix41 sus = matrixMultiplication44_41(a, b);
    Matrix41 target = {-117, 101, 45, 26};
    cester_assert_cmp(compareMatrix41(sus, target), ==, 1);
)

CESTER_TEST(TestIdenticalCollision, TestPhysics,
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
    cester_assert_cmp(colliding, ==, 1);
)

CESTER_TEST(TestNonCollision, TestPhysics,
    // create CollisionBody for object
    CollisionBody* collisionBody1 = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody1);
    // create collider
    BoxCollider *collider1 = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider1);
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
    collider1->xLen = 1.f;
    collider1->yLen = 1.f;
    collider1->zLen = 1.f;
    CollisionBody_addBoxCollider(collisionBody2, collider2);
    CollisionBody_translate(collisionBody2, 1.1f, 0.f, 0.f);

    cester_assert_cmp(!testAABBCollision(collisionBody1, collisionBody2), ==, false);
)

CESTER_TEST(TestAABBRotationX, TestPhysics,
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

    cester_assert_cmp(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy1, -3.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBx2, 1.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBy2, 0.f, 0.0001f) &&
                      fTolerance(collisionBody->AABBz2, 2.f, 0.0001f), ==, true);
)

CESTER_TEST(TestAABBRotationY, TestPhysics,
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

    cester_assert_cmp(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz1, -1.f, 0.0001f) &&
       fTolerance(collisionBody->AABBx2, 3.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy2, 2.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz2, 0.f, 0.0001f), ==, true);
)

CESTER_TEST(TestAABBRotationZ, TestPhysics,
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

    cester_assert_cmp(fTolerance(collisionBody->AABBx1, -2.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBx2, 0.f, 0.0001f) &&
       fTolerance(collisionBody->AABBy2, 1.f, 0.0001f) &&
       fTolerance(collisionBody->AABBz2, 3.f, 0.0001f), ==, true);
)

CESTER_TEST(TestAABBStackedRotation, TestPhysics,
    // create CollisionBody for object
    CollisionBody* collisionBody = calloc(1, sizeof(CollisionBody));
    CollisionBody_init(collisionBody);
    // create collider
    BoxCollider* collider = calloc(1, sizeof(BoxCollider));
    BoxCollider_init(collider);
    collider->xLen = 1.f;
    collider->yLen = 2.f;
    collider->zLen = 3.f;
    collider->xRot = 180.f;

    CollisionBody_addBoxCollider(collisionBody, collider);
    CollisionBody_setRot(collisionBody, 180.f, 0.f, 0.f);

    cester_assert_cmp(fTolerance(collisionBody->AABBx1, 0.f, 0.0001f) &&
    fTolerance(collisionBody->AABBy1, 0.f, 0.0001f) &&
    fTolerance(collisionBody->AABBz1, 0.f, 0.0001f) &&
    fTolerance(collisionBody->AABBx2, 1.f, 0.0001f) &&
    fTolerance(collisionBody->AABBy2, 2.f, 0.0001f) &&
    fTolerance(collisionBody->AABBz2, 3.f, 0.0001f), ==, true);
)
*/

CESTER_BODY(
bool beginUnitTests(int argc, char* argv[]) {
    CESTER_REGISTER_TEST(test_one);
    //CESTER_REGISTER_TEST(TestIdentity44);
    //CESTER_REGISTER_TEST(TestMatrixMultiplication44_44);
    //CESTER_REGISTER_TEST(TestMatrixMultiplication44_41);
    //CESTER_REGISTER_TEST(TestIdenticalCollision);
    //CESTER_REGISTER_TEST(TestNonCollision);
    //CESTER_REGISTER_TEST(TestAABBRotationX);
    //CESTER_REGISTER_TEST(TestAABBRotationY);
    //CESTER_REGISTER_TEST(TestAABBRotationZ);
    //CESTER_REGISTER_TEST(TestAABBStackedRotation);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
