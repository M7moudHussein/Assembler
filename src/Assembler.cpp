#include <iostream>
#include "Machine.h"
#include "Pass1.hpp"

int main(int argc, char **argv) {
    if(argc == 2)
        Machine(std::string(argv[1]));
    else
        Machine(std::string("input.txt"));
    return 0;
}