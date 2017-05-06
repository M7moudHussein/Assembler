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

Pass1::Pass1(std::string inputFile): _inputFile(inputFile){
    symbolTable = new SymbolTable;
    _startingAddress = 0;
    _hasError = false;
    compute();
};

SymbolTable* Pass1::getSymbolTable() {
    return symbolTable;
}

std::string Pass1::getInterFile(){
    return INTER_FILE;
}

int Pass1::getStartingAddress() {
    return _startingAddress;
}

int Pass1::getProgramLength() {
    return _programLength;
}

std::vector<Line> Pass1::getProgramCode() {
    return _programCode;
}

bool Pass1::fail(){
    return _hasError;
}

void Pass1::compute() {
    _locCtr = 0;
    std::ifstream inputStream(_inputFile);
    std::ofstream outputStream(INTER_FILE);
    while (std::getline(inputStream, _stringInput)) {
        Line lineCommand(_stringInput, _locCtr);
        _hasError = handleLine(lineCommand, outputStream) || _hasError;
        outputStream << lineCommand << std::endl;
        if (lineCommand.isEnd())
            break;
    }
//    assert(inputStream.eof());
    inputStream.close();
    outputStream.close();
    _programLength = _locCtr - _startingAddress;
}

bool Pass1::handleLine(Line lineCommand, std::ofstream& outputStream){
    if(!lineCommand.isComment()){
        _programCode.push_back(lineCommand);
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
        _locCtr = lineCommand.getNextAddress();
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