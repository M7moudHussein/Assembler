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

bool Pass1::fail(){
    return _hasError;
}

void Pass1::compute() {
    _locCtr = 0;
    std::string _stringInput;
    std::ifstream inputStream(_inputFile);
    std::ofstream intermedStream(INTER_FILE);
    while (std::getline(inputStream, _stringInput)) {
        Line lineCommand(_stringInput, _locCtr);
        _hasError = handleLine(lineCommand, intermedStream) || _hasError;
        if(_locCtr > std::stoi(std::string("ffff"), nullptr, 16)){
            _hasError = true;
            intermedStream << "Location counter out of bounds\n";
        }
        if(!lineCommand.isComment())
            intermedStream << lineCommand << std::endl;
        if (lineCommand.isEnd())
            break;
    }
    assert(inputStream.eof());
    inputStream.close();
    intermedStream.close();
    _programLength = _locCtr - _startingAddress;
}

bool Pass1::handleLine(Line lineCommand, std::ofstream& intermedStream){
    if(!lineCommand.isComment()){
        if (lineCommand.fail()) {
            intermedStream << lineCommand.getError() << "\n";
            return true;
        } else {
            if ((!lineCommand.isStart()) && lineCommand.hasLabel()) {
                if (!addLabel(lineCommand.getLabel(), lineCommand.getIntAddress())) {
                    intermedStream << "Duplicate Label has appeared, Error\n" << std::endl;
                    return true;
                }
            }
            _locCtr = lineCommand.getNextAddress();
            if(lineCommand.isStart())
                _startingAddress = _locCtr;
        }
    }
    return false;
}

bool Pass1::addLabel(std::string label, int address) {
    if (symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}