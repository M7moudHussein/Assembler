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
            outputStream << lineCommand.getError();
        }
        if (lineCommand.getOperand() == "end") {
            state = ProgramState::END;
        }
        switch (state) {
            case ProgramState::START:
                if (lineCommand.getOperation() != "start") {
                    state = ProgramState::PROGRAM;
                    std::stringstream ss;
                    ss << std::hex << lineCommand.getOperand();
                    ss >> locCtr;
                } else {
                    locCtr = lineCommand.getNextAddress(locCtr);
                    lineCommand.setAddress(locCtr);
                    state = ProgramState::PROGRAM;
                    startingAddress = locCtr;
                    break;
                }
            case ProgramState::PROGRAM:
                if (lineCommand.hasLabel()) {
                    if (!addLabel(lineCommand.getLabel(), locCtr)) {
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
    std::string outputFile = "objectcode.txt";
    std::ifstream inputStream(INTER_FILE);
    std::ofstream outputStream(outputFile);
    std::string inputLine, firstInstructionAddress;
    getline(inputStream, inputLine);
    std::vector<std::string> line = parseLine(inputLine);
    firstInstructionAddress = line[0];

    outputStream << "H^" << line[1] << "\t" << formalize(firstInstructionAddress, 6) << "^"
                 << to_hexadecimal(programLength)
                 << std::endl;
    TextRecord textRecord;
    while (getline(inputStream, inputLine)) {
        int opCode;
        std::string operandAddress;
        std::string objectCode;
        line = parseLine(inputLine);
        if (line[2] == "end") {
            break;
        }
        //TODO check if no a comment line. (i don't now how a comment will be in intermediate file).
        {
            if (OperationTable::getInstance()->hasOperation(line[2])) { //line has a valid operation.
                opCode = OperationTable::getInstance()->getOpCode(line[2]);
                if (!line[3].empty()) { //has an operand
                    if (symbolTable->hasLabel(line[3])) { //a valid operand
                        operandAddress = to_hexadecimal(symbolTable->getAddress(line[3]));
                    } else {
                        operandAddress = "0";
                        //TODO Error handling (undefined symbol).
                    }
                } else {
                    operandAddress = "0";
                }
                objectCode = formalize(to_hexadecimal(opCode), 2) + formalize(operandAddress, 4);
            } else if (line[2] == "byte" || line[2] == "word") { //if byte or word
                if (line[2] == "byte") {
                    objectCode = line[3].substr(2, line[3].length() - 3);
                } else {
                    objectCode = formalize(to_hexadecimal(line[3]), 6);
                }
            } else {
                //TODO Error handling un supported operation.
                objectCode = "XXXXXX";
            }
            if (!textRecord.fits(objectCode)) {
                outputStream << textRecord.to_string();
                textRecord = TextRecord();
            } else {
                textRecord.append(objectCode, line[0]);
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

std::vector<std::string> Machine::parseLine(std::string &line) {
    std::vector<std::string> lineParts;
    lineParts.push_back(line.substr(0, 4));
    int it = 5;
    if (isspace(line[it])) {
        lineParts.push_back(std::string());
    } else {
        while (it < line.length() && !isspace(line[it]))it++;
        lineParts.push_back(line.substr(5, it - 5));
    }
    while (it < line.length() && isspace(line[it]))it++;
    int temp = it;
    while (it < line.length() && !isspace(line[it]))it++;
    lineParts.push_back(line.substr(temp, it - temp));
    while (it < line.length() && isspace(line[it]))it++;
    temp = it;
    while (it < line.length() && !isspace(line[it]))it++;
    lineParts.push_back(line.substr(temp, it - temp));
    for (int i = 0; i < (int) lineParts.size(); i++) {
        std::transform(lineParts[i].begin(), lineParts[i].end(), lineParts[i].begin(), ::tolower);
    }
    return lineParts;
}

std::string Machine::to_hexadecimal(std::string number) {
    std::stringstream stream;
    stream << std::hex << number;
    return stream.str();
}

std::string Machine::to_hexadecimal(int number) {
    return to_hexadecimal(std::to_string(number));
}

std::string Machine::formalize(std::string code, int len) {
    while (code.length() < len) {
        code = "0" + code;
    }
    return code;
}