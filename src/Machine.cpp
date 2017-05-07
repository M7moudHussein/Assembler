#include "Machine.h"

Machine::Machine(std::string inputFile) : inputFile(inputFile) {
    assemble();
}

Machine::~Machine() {
}

void Machine::assemble() {
    Pass1 pass1(inputFile);
    if (pass1.fail()) {
        std::cout << "Pass1 Failed Check the Lisa and Intermediate Files\n";
        std::cout << "The program will stop and not execute Pass2";
    } else {
        Pass2 pass2(pass1.getSymbolTable(), pass1.getInterFile(), pass1.getProgramLength());
        try {
            std::string inputName = inputFile.substr(0, inputFile.length() - 4);
            pass2.generateObjFile("output/" + inputName + "-objectcode.obj", "output/" + inputName + "-listing_file.txt");
        } catch (const char *message) {
            std::cout << message << std::endl;
        }
        std::cout << "Program Finished Successfully";
    }
}