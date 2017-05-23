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
    litTable = new LiteralTable;
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
    std::string intermedData = "";
    while (std::getline(inputStream, _stringInput)) {
        std::cout << "HELO\n";
        Line lineCommand(_stringInput, _locCtr, symbolTable);
        _hasError = handleLine(lineCommand, intermedData) || _hasError;
        if(_locCtr > std::stoi(std::string("ffff"), nullptr, 16) || _locCtr < 0){
            _hasError = true;
            intermedData += "Location counter out of bounds\n";
            std::cout << "Out of Memory bounds of SIC Machine" << std::endl;
        }
        std::stringstream ss;
        ss << lineCommand << std::endl;
        intermedData += ss.str();
        if (lineCommand.isEnd())
            break;
    }
    printSymbolTable(intermedStream);
    printLiteralTable(intermedStream);
    intermedStream << intermedData;
    inputStream.close();
    intermedStream.close();
    _programLength = _locCtr - _startingAddress;
}


bool Pass1::handleLine(Line lineCommand, std::string& intermedData){
    if(!lineCommand.isComment()){
        if (lineCommand.fail()) {
            intermedData += lineCommand.getError() + "\n";
            return true;
        } else {
            if(lineCommand.isLTORG() || lineCommand.isEnd())
                litTable->arrangeTable(_locCtr);
            if(lineCommand.hasLiteral())
                litTable->addLiteral(lineCommand.getOperand());
            if ((!lineCommand.isStart()) && (!lineCommand.isEQU()) && lineCommand.hasLabel()) {
                if (!addLabel(lineCommand.getLabel(), lineCommand.getIntAddress())) {
                    intermedData += "Duplicate Label has appeared, Error\n";
                    return true;
                }
            }
            if(!lineCommand.isEQU())
                _locCtr = lineCommand.getNextAddress(symbolTable);
            else{
                if (!addLabel(lineCommand.getLabel(), lineCommand.getNextAddress(symbolTable))) {
                    intermedData += "Duplicate Label has appeared, Error\n";
                    return true;
                }
            }
            if(lineCommand.isStart())
                _startingAddress = _locCtr;
        }
    }
    return false;
}

void Pass1::printSymbolTable(std::ofstream &intermedStream) {
    std::vector<std::pair<std::string, int> > vec = symbolTable->getData();
    intermedStream << vec.size() << "\n";
    for(int i = 0; i < vec.size(); i++) {
        intermedStream << vec[i].first << '\t'<< vec[i].second;
    }
    intermedStream << std::endl;
}

void Pass1::printLiteralTable(std::ofstream &intermedStream){
    std::vector<std::pair<std::string, int> > vec = litTable->getData();
    intermedStream << vec.size() << "\n";
    for(int i = 0; i < vec.size(); i++) {
        intermedStream << vec[i].first << '\t'<< vec[i].second;
    }
    intermedStream << std::endl;
}

bool Pass1::addLabel(std::string label, int address) {
    if (symbolTable->hasLabel(label))
        return false;
    symbolTable->addLabel(label, address);
    return true;
}