#include "Machine.h"

Machine::Machine(std::string inputFile, std::string outputFile) : inputFile(inputFile), outputFile(outputFile) {
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
            pass2.generateObjFile("output/"+outputFile, "output/listing_file.txt");
        } catch (const char *message) {
            std::cout << message << std::endl;
        }
        std::cout << "Program Finished Successfully";
    }
}