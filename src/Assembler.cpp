#include <iostream>
#include "Machine.h"

int main(int argc, char **argv) {
    Machine machine("input.txt");
    machine.assemble();
    return 0;
}