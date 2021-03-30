#include <string.h>
#include <stdio.h>
#include "Engine/engine.h"
#include "tests/tests.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        return UnitMain();
    } else {
        return Engine_run(argc, argv);
    }
}
