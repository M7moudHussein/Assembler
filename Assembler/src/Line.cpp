/*
 * Line.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "Line.h"
#include "OperationTable.h"
#include <iostream>

Line::Line(std::string line) {
	parseLine(line);
}

Line::~Line() {

}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
    os << std::hex << line.address << std::dec << '\t' << line.label << '\t' << line.operation
                << '\t' << line.operand << '\t' << line.comment;
    return os;
}

void Line::parseLine(std::string line){
    ReadState state = ReadState::LABEL;
    int pos = 0;
    int len = line.length();
    while(pos < len){
        char curChar = line[pos];
        if(isspace(curChar)){
            state = getNextState(state);
            while(pos < len - 1 && isspace(line[pos])) pos++;
            continue;
        }
        switch(state){
            case ReadState::LABEL:
                label += curChar;
                readLabel = true;
                pos++;
                break;
            case ReadState::OPERATION:
                operation += curChar;
                readOperation = true;
                pos++;
                break;
            case ReadState::OPERAND:
                operand += curChar;
                readOperand = true;
                pos++;
                break;
            case ReadState::COMMENT:
                for(; pos < len; pos++)
                    comment += line[pos];
                readComment = true;
        }
    }
    reformData();
}

void Line::reformData(){
    reformLabel();
}

void Line::reformLabel(){
    if(label.length() == 0)
        readLabel = false;
}

ReadState Line::getNextState(ReadState curState){
    switch(curState){
        case ReadState::LABEL:
            return ReadState::OPERATION;
        case ReadState::OPERATION:
            return ReadState::OPERAND;
        case ReadState::OPERAND:
            return ReadState::COMMENT;
        default:
            return ReadState::INVALID;
    }
}

bool Line::hasLabel(){
    return readLabel;
}

bool Line::hasOperation() {
    return readOperation;
}

bool Line::hasOperand() {
    return readOperand;
}

bool Line::hasComment() {
    return readComment;
}

std::string Line::getLabel() {
    return label;
}

std::string Line::getOperation() {
    return operation;
}

std::string Line::getOperand() {
    return operand;
}

std::string Line::getComment() {
    return comment;
}

void Line::setAddress(int address)  {
    this->address = address;
}

bool Line::isValid(){
    if(operation == "resw" || operation == "resb" || operation == "word")
        return validInteger(operand);
    if(operation == "byte")
        return validByte(operand);
    return true;
}

bool Line::validInteger(std::string integer) {
    for(int i = 0; i < integer.length(); i++){
        int curVal = integer[i] - '0';
        if(curVal < 0 || curVal > 9)
            return false;
    }
    return true;
}

bool Line::validByte(std::string charSeq) {
    if(charSeq.length() < 3) return false;
    char firstChar = tolower(charSeq[0]);
    if(firstChar != 'c' && firstChar != 'f') return false;
    if(charSeq[1] != '\'' || charSeq[charSeq.length() - 1] != '\'') return false;
    if(firstChar == 'f'){
        for(int i = 2; i < charSeq.length() - 1; i++){
            int value = charSeq[i] - '0';
            int alphaVal = charSeq[i] - 'a';
            if((value >= 0 & value <= 9) || (alphaVal >= 0 && alphaVal <= 5))
                continue;
            return false;
        }
    }
    return true;
}

std::string Line::getError() {
    return std::string();
}

int Line::getNextAddress(int locCtr){
    if(operation == "start")
        return std::stoi(operand, nullptr, 16);
    if(!isValid()){
        return locCtr;
    }
    OperationTable* opTable = OperationTable::getInstance();
    if(opTable->hasOperation(operation) || operation == "word"){
        return 3 + locCtr;
    }else if(operation == "resw"){
        return 3 * std::stoi(operand) + locCtr;
    }else if(operation == "resb"){
        return std::stoi(operand) + locCtr;
    }else if(operation == "byte"){
        return getConstSize() + locCtr;
    }
}

int Line::getConstSize(){
    char firstChar = tolower(operand[0]);
    if(firstChar == 'c')
        return operand.length() - 3;
    return (operand.length() - 3 + 1) / 2;
}