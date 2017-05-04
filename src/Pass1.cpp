#include "Pass1.hpp"
#include "Line.h"
#include "OperationTable.h"
#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "Util.hpp"

Pass1::Pass1(std::string inputFile): inputFile(inputFile){
    symbolTable = new SymbolTable;
    startingAddress = 0;
    hasError = false;
    compute();
};

SymbolTable* Pass1::getSymbolTable() {
    return symbolTable;
}

std::string Pass1::getInterFile(){
    return INTER_FILE;
}

int Pass1::getStartingAddress() {
    return startingAddress;
}

int Pass1::getProgramLength() {
    return programLength;
}

bool Pass1::fail(){
    return hasError;
}

void Pass1::compute() {
    locCtr = 0;
    std::ifstream inputStream(inputFile);
    std::ofstream outputStream(INTER_FILE);
    while (std::getline(inputStream, stringInput)) {
        Line lineCommand(stringInput, locCtr);
        hasError = handleLine(lineCommand, outputStream) || hasError;
        outputStream << lineCommand << std::endl;
        if (lineCommand.isEnd())
            break;
    }
    assert(inputStream.eof());
    inputStream.close();
    outputStream.close();
    programLength = locCtr - startingAddress;
}

bool Pass1::handleLine(Line lineCommand, std::ofstream& outputStream){
    if(!lineCommand.isComment()){
        if (lineCommand.fail()) {
            outputStream << lineCommand.getError() << "\n";
            return true;
        } else {
            if ((!lineCommand.isStart()) && lineCommand.hasLabel()) {
                if (!addLabel(lineCommand.getLabel(), lineCommand.getIntAddress())) {
                    outputStream << "Duplicate Label has appeared, Error\n" << std::endl;
                    return true;
                }
            }
        }
        locCtr = lineCommand.getNextAddress();
    }
    return false;
}
void Pass1::printLisaFile() {
    std::ofstream outputStream(LISA_FILE);
    std::vector<std::pair<std::string, int> > vec = symbolTable->getData();
    for(int i = 0; i < vec.size(); i++){
        outputStream << vec[i].first << "\t" << vec[i].second << std::endl;
    }
    outputStream.close();
}

bool Pass1::addLabel(std::string label, int address) {
    if (symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}