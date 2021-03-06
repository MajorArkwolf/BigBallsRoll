#include <string.h>
#include <stdio.h>
#include "Engine/engine.h"
#include "UnitTest/unitTestEntry.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        printf("We do the test");
        beginUnitTests(argc, argv);
    } else {
        return Engine_run(argc, argv);
    }
}
