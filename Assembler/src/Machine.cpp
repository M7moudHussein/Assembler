/*
 * Machine.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "Machine.h"
#include "Line.h"
#include "OperationTable.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

Machine::Machine(std::string inputFile) : inputFile(inputFile) {
	symbolTable = new SymbolTable;
    startingAddress = 0;
}

Machine::~Machine() {
	delete symbolTable;
}

void Machine::assemble() {
    int errorMask = pass1(inputFile);
    pass2();
}

int Machine::pass1(std::string inputFile) {
    int locCtr = 0;
    std::ifstream inputStream(inputFile);
    std::ofstream outputStream(INTER_FILE);
    std::string stringInput;
    ProgramState state = ProgramState::START;
    while(std::getline(inputStream, stringInput)){
        Line lineCommand(stringInput);
        if(!lineCommand.isValid()){
            outputStream << lineCommand.getError();
        }
        if(lineCommand.getOperand() == "end"){
            state = ProgramState::END;
        }
        switch(state){
            case ProgramState::START:
                if(lineCommand.getOperation() != "start"){
                    state = ProgramState::PROGRAM;
                    locCtr = 0;
                }else {
                    locCtr = lineCommand.getNextAddress(locCtr);
                    lineCommand.setAddress(locCtr);
                    state = ProgramState::PROGRAM;
                    startingAddress = locCtr;
                    break;
                }
            case ProgramState::PROGRAM:
                if(lineCommand.hasLabel()){
                    if(!addLabel(lineCommand.getLabel(), locCtr)){
                        outputStream << "Duplicate Label has appeared, Error\n";
                    }
                }
                lineCommand.setAddress(locCtr);
                locCtr = lineCommand.getNextAddress(locCtr);
                break;
            case ProgramState::END:
                break;
        }
        outputStream << lineCommand << std::endl;
    }
    assert(inputStream.eof());
    inputStream.close();
    programLength = locCtr - startingAddress;
}

void Machine::pass2() {

}


bool Machine::addLabel(std::string label, int address) {
    if(symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}