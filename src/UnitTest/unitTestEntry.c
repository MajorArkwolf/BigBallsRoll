#include "unitTestEntry.h"
#include "ModelUnitTests.h"
#include "cester.h"

// For more information on how to add and do unit tests view these links.
// https://exoticlibraries.github.io/libcester/docs/manual_test_registration.html


CESTER_TEST(test_one, inst,
        cester_assert_equal(NULL, ((void*)0));
)

CESTER_BODY(
bool beginUnitTests(int argc, char* argv[]) {
    CESTER_REGISTER_TEST(obj_vert_test);
    CESTER_REGISTER_TEST(obj_face_test);
    CESTER_REGISTER_TEST(obj_normal_test);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
