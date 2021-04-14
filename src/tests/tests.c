#include <unity.h>
#include "ModelUnitTests.h"
#include "PhysicsUnitTests.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int UnitMain() {
    UNITY_BEGIN();
    //RUN_TEST(test_ModelLoader);
    RUN_TEST(test_Physics);
    return UNITY_END();
}