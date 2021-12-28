#include "listapp.h"

#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
    setvbuf(stdout, nullptr, _IONBF, 0);
    auto list = GetAppList();

    for (auto ite : list) {
        std::cout << ite.name << "'s version: \t" << ite.version << std::endl;
    }
    return 0;
}
