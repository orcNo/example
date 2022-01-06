#include "listapp.h"

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
#ifdef WIN32
    setvbuf(stdout, nullptr, _IONBF, 0);
    auto list = GetAppList();

    for (auto ite : list) {
        std::cout << ite.name << "'s version: \t" << ite.version << std::endl;
    }
#endif
    return 0;
}
