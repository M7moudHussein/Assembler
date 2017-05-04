//
// Created by Mohamed Ayman on 5/3/2017.
//

#include "Pass2.hpp"

Pass2::Pass2(SymbolTable* symbolTable, std::string interFile, int programLength):
        symbolTable(symbolTable), _interFile(interFile), _programLength(programLength){

}

void Pass2::generateObjFile(std::string output){
    compute(output);
}

void Pass2::compute(std::string output) {
    std::ifstream inputStream(_interFile);
    std::ofstream outputStream(output);
    Line line;
    std::string firstInstructionAddress;
    inputStream >> line;
    firstInstructionAddress = line.getHexAddress();
    outputStream << "H^" << line.getLabel() << "\t" << Util::formalize(firstInstructionAddress, 6) << "^"
                 << Util::to_hexadecimal(_programLength)
                 << std::endl;
    TextRecord textRecord;
    while (inputStream >> line) {
        int opCode;
        std::string operandAddress;
        std::string objectCode;
        if (line.isEnd()) {
            break;
        }
        if(!line.isComment())
        {
            if (OperationTable::getInstance()->hasOperation(line.getOperation())) { //line has a valid _operation.
                opCode = OperationTable::getInstance()->getOpCode(line.getOperation());
                if (line.hasOperand()) { //has an _operand
                    if (symbolTable->hasLabel(line.getOperand())) { //a valid _operand
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
                //TODO Error handling un supported _operation.
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
