/*
 * Machine.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "Machine.h"

Machine::Machine(std::string inputFile) : inputFile(inputFile) {
	symbolTable = new SymbolTable;
}

Machine::~Machine() {
	delete symbolTable;
}

void Machine::assemble() {
    std::string intermedFile = pass1(inputFile);
    pass2(intermedFile);
}

std::string Machine::pass1(std::string inputFile) {

}

void Machine::pass2(std::string intermedFile) {
    symbolTable = readIntermediateFile();

}