#include "Machine.h"
#include "Line.h"
#include "TextRecord.h"
#include "OperationTable.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "Util.hpp"

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
    while (std::getline(inputStream, stringInput)) {
        Line lineCommand(stringInput);
        if (!lineCommand.isValid()) {
//            outputStream << lineCommand.getError();
        }
        if (lineCommand.getOperand() == "end") {
            break;
        }
        switch (state) {
            case ProgramState::START:
                state = ProgramState::PROGRAM;
                if ((!Util::equalsIgnoreCase(lineCommand.getOperation(), "start")) || !lineCommand.hasOperand()) {
                    //print error
                } else {
                    locCtr = lineCommand.setAddress(locCtr);
                    startingAddress = locCtr;
                    break;
                }
            case ProgramState::PROGRAM:
                if (lineCommand.hasLabel()) {
                    if (!addLabel(lineCommand.getLabel(), locCtr)) {
                        outputStream << "Duplicate Label has appeared, Error\n";
                    }
                }
                locCtr = lineCommand.setAddress(locCtr);
                break;
        }
        outputStream << lineCommand << std::endl;
    }
    assert(inputStream.eof());
    inputStream.close();
    programLength = locCtr - startingAddress;
}

void Machine::pass2() {
    std::string outputFile = "objectcode.txt";
    std::ifstream inputStream(INTER_FILE);
    std::ofstream outputStream(outputFile);
    Line line;
    std::string firstInstructionAddress;
    inputStream >> line;
    firstInstructionAddress = line.getHexAddress();
    outputStream << "H^" << line.getLabel() << "\t" << Util::formalize(firstInstructionAddress, 6) << "^"
                 << Util::to_hexadecimal(programLength)
                 << std::endl;
    TextRecord textRecord;
    while (inputStream >> line) {
        int opCode;
        std::string operandAddress;
        std::string objectCode;
        if (line.isEnd()) {
            break;
        }
        //TODO check if no a comment line. (i don't now how a comment will be in intermediate file).
        {
            if (OperationTable::getInstance()->hasOperation(line.getOperation())) { //line has a valid operation.
                opCode = OperationTable::getInstance()->getOpCode(line.getOperation());
                if (line.hasOperand()) { //has an operand
                    if (symbolTable->hasLabel(line.getOperand())) { //a valid operand
                        operandAddress = Util::to_hexadecimal(symbolTable->getAddress(line.getOperand()));
                    } else {
                        operandAddress = "0";
                        //TODO Error handling (undefined symbol).
                    }
                } else {
                    operandAddress = "0";
                }
                objectCode = Util::formalize(Util::to_hexadecimal(opCode), 2) + Util::formalize(operandAddress, 4);
            } else if (Util::equalsIgnoreCase(line.getOperation(), "byte") ||
                       Util::equalsIgnoreCase(line.getOperation(), "word")) { //if byte or word
                if (Util::equalsIgnoreCase(line.getOperation(), "byte")) {
                    objectCode = line.getOperand().substr(2, line.getOperand().length() - 3);
                } else {
                    objectCode = Util::formalize(Util::to_hexadecimal(line.getOperand()), 6);
                }
            } else {
                //TODO Error handling un supported operation.
                objectCode = "XXXXXX";
            }
            if (!textRecord.fits(objectCode)) {
                outputStream << textRecord << std::endl;
                textRecord = TextRecord();
            } else {
                textRecord.append(objectCode, line.getHexAddress());
            }
        }
    }
    if (!textRecord.empty()) {
        outputStream << textRecord << std::endl;
    }
    outputStream << "E^" << Util::formalize(firstInstructionAddress, 6) << std::endl;
}

bool Machine::addLabel(std::string label, int address) {
    if (symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}