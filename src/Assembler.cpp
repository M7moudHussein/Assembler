#include <iostream>
#include "Machine.h"
#include "Pass1.hpp"

int main(int argc, char **argv) {
    if(argc == 2)
        Machine(std::string(argv[1]));
    return 0;
}