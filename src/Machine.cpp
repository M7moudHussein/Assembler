/*
 * Machine.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

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
                if ((!equalsIgnoreCase(lineCommand.getOperation(), "start")) || !lineCommand.hasOperand()) {
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
    outputStream << "H^" << line.getOperation() << "\t" << formalize(firstInstructionAddress, 6) << "^"
                 << to_hexadecimal(programLength)
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
                        operandAddress = to_hexadecimal(symbolTable->getAddress(line.getOperand()));
                    } else {
                        operandAddress = "0";
                        //TODO Error handling (undefined symbol).
                    }
                } else {
                    operandAddress = "0";
                }
                objectCode = formalize(to_hexadecimal(opCode), 2) + formalize(operandAddress, 4);
            } else if (equalsIgnoreCase(line.getOperation(), "byte") ||
                       equalsIgnoreCase(line.getOperation(), "word")) { //if byte or word
                if (equalsIgnoreCase(line.getOperation(), "byte")) {
                    objectCode = line.getOperand().substr(2, line.getOperand().length() - 3);
                } else {
                    objectCode = formalize(to_hexadecimal(line.getOperand()), 6);
                }
            } else {
                //TODO Error handling un supported operation.
                objectCode = "XXXXXX";
            }
            if (!textRecord.fits(objectCode)) {
                outputStream << textRecord.to_string();
                textRecord = TextRecord();
            } else {
                textRecord.append(objectCode, line.getHexAddress());
            }
        }
    }
    if (!textRecord.empty()) {
        outputStream << textRecord.to_string();
    }
    outputStream << "E^" << formalize(firstInstructionAddress, 6) << std::endl;
}

bool Machine::addLabel(std::string label, int address) {
    if (symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}

//std::vector<std::string> Machine::parseLine(std::string &line) {
//    std::vector<std::string> lineParts;
//    int it = 0;
//    if (!isspace(line[it])) {
//        lineParts.push_back(line.substr(0, 4));
//        it = 5;
//    } else {
//        lineParts.push_back(std::string());
//    }
//    if (isspace(line[it])) {
//        lineParts.push_back(std::string());
//    } else {
//        while (it < line.length() && !isspace(line[it]))it++;
//        lineParts.push_back(line.substr(5, it - 5));
//    }
//    while (it < line.length() && isspace(line[it]))it++;
//    int temp = it;
//    while (it < line.length() && !isspace(line[it]))it++;
//    lineParts.push_back(line.substr(temp, it - temp));
//    while (it < line.length() && isspace(line[it]))it++;
//    temp = it;
//    while (it < line.length() && !isspace(line[it]))it++;
//    lineParts.push_back(line.substr(temp, it - temp));
//    for (int i = 0; i < (int) lineParts.size(); i++) {
//        std::transform(lineParts[i].begin(), lineParts[i].end(), lineParts[i].begin(), ::tolower);
//    }
//    return lineParts;
//}

std::string Machine::to_hexadecimal(int number) {
    std::stringstream stream;
    stream << std::hex << number;
    return stream.str();
}

std::string Machine::to_hexadecimal(std::string number) {
    return to_hexadecimal(stoi(number));
}

std::string Machine::formalize(std::string code, int len) {
    while (code.length() < len) {
        code = "0" + code;
    }
    return code;
}

bool Machine::equalsIgnoreCase(const std::string &str1, const char *str2) const {
    if (str1.length() != std::strlen(str2)) {
        return false;
    }
    for (int i = 0; i < str1.length(); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }
    return true;
}