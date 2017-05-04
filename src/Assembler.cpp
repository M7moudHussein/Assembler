#include <iostream>
#include "Machine.h"
#include "Pass1.hpp"

int main(int argc, char **argv) {
    Pass1 pass1("input.txt");
    pass1.printLisaFile();
    return 0;
}