#include "unitTestEntry.h"
#define CESTER_NO_MAIN
#include <exotic/cester.h>

// For more information on how to add and do unit tests view these links.
// https://exoticlibraries.github.io/libcester/docs/manual_test_registration.html


CESTER_TEST(test_one, inst,
        cester_assert_equal(NULL, ((void*)0));
)

CESTER_BODY(
bool beginUnitTests(int argc, char* argv[]) {
    CESTER_REGISTER_TEST(test_one);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
