//
// Created by Mohamed Ayman on 5/3/2017.
//

#include "Pass2.hpp"

Pass2::Pass2(SymbolTable *symbolTable, std::string interFile, int programLength) :
        symbolTable(symbolTable), _interFile(interFile), _programLength(programLength) {
}

void Pass2::generateObjFile(std::string output) {
    compute(output);
}

#include <iostream>

void Pass2::compute(std::string output) {
    std::ofstream outputStream(output);
    std::ifstream interStream(_interFile);
    TextRecord textRecord;
    std::string startAddress;
    while(!interStream.eof()){
        Line line;
        line.read(&interStream);
        if (line.isStart()) {
            outputStream << buildHeader(line, startAddress) << std::endl;
        } else if (line.isEnd()) {
            if (!textRecord.empty()) {
                outputStream << textRecord << std::endl;
            }
            outputStream << buildEnd(startAddress) << std::endl;
            break;
        } else {
            std::string objectCode = line.getObjectCode(*symbolTable);
            if (textRecord.empty())
                textRecord.setStartingAddress(Util::formalize(line.getAddress(), 6));
            if (!textRecord.fits(objectCode)) {
                outputStream << textRecord << std::endl;
                textRecord = TextRecord();
            }
            textRecord.append(objectCode);
        }
    }
    std::cout << "OUT";
    outputStream.close();
}

std::string Pass2::buildHeader(Line line, std::string &startAddress) {
    std::string ret;
    ret.append("H");
    ret.append(Util::SEPARATOR);
    ret.append(line.getLabel());
    ret.append("\t");
    ret.append(Util::SEPARATOR);
    ret.append(Util::formalize(Util::to_hexadecimal(_programLength), 6));
    ret.append(Util::SEPARATOR);
    ret.append(Util::formalize(line.getOperand(), 6));
    startAddress = line.getOperand();
    return ret;
}

std::string Pass2::buildEnd(std::string startAddress) {
    return "E" + Util::SEPARATOR + Util::formalize(startAddress, 6);
}