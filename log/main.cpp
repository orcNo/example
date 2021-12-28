#include "logger.h"

#include <stdio.h>

int main(int argc, char** argv) {
    setvbuf(stdout, nullptr, _IONBF, 0);

    Logger log;
    log << __FUNCTION__ << "xxx\n";
    printf("%s", "xxxxxxxxxx");
    fflush(stdout);

    return 0;
}
