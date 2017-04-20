
#include "Line.h"
#include "OperationTable.h"
#include <iostream>
#include <cstring>

Line::Line(std::string line) {
    parseLine(line);
}

Line::Line(){

}

Line::~Line() {

}

std::ostream &operator<<(std::ostream &os, const Line &line) {
    if(!line.isEnd()){
        os << std::hex << line.address << std::dec << "\t";
    }else{
        os << " ";
    }
    os << (line.hasLabel() ? line.label : " ") << '\t'
       << line.operation << '\t'
       << (line.hasOperand() ? line.operand : " ") << '\t'
       << (line.hasComment() ? line.comment : " ");
    return os;
}

std::istream& operator >> (std::istream& is, Line& c)
{
    std::string firstWord;
    is >> firstWord;
    if(!c.equalsIgnoreCase(firstWord, "end")){
        c.address = stoi(firstWord, nullptr, 16);
        is >> c.label;
    }else{
        c.label = firstWord;
    }
    is >> c.operation >> c.operand >> c.comment;
    return is;
}
void Line::parseLine(std::string line) {
    ReadState state = ReadState::LABEL;
    int pos = 0;
    int len = line.length();
    while (pos < len) {
        char curChar = line[pos];
        if (isspace(curChar)) {
            state = getNextState(state);
            while (pos < len - 1 && isspace(line[pos])) pos++;
            continue;
        }
        switch (state) {
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
                for (; pos < len; pos++)
                    comment += line[pos];
                readComment = true;
        }
    }
    reformData();
}

void Line::reformData() {
    reformLabel();
}

void Line::reformLabel() {
    if (label.length() == 0)
        readLabel = false;
}

ReadState Line::getNextState(ReadState curState) {
    switch (curState) {
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

bool Line::hasLabel() const{
    return label.length() != 0;
}

bool Line::hasOperand() const {
    return operand.length() != 0;
}

bool Line::hasComment() const{
    return comment.length() != 0;
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

int Line::getAddress(){
    return address;
}

std::string Line::getComment() {
    return comment;
}

void Line::setAddress(int address) {
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
    if (charSeq.length() < 3) return false;
    char firstChar = tolower(charSeq[0]);
    if (firstChar != 'c' && firstChar != 'f') return false;
    if (charSeq[1] != '\'' || charSeq[charSeq.length() - 1] != '\'') return false;
    if (firstChar == 'f') {
        for (int i = 2; i < charSeq.length() - 1; i++) {
            int value = charSeq[i] - '0';
            int alphaVal = charSeq[i] - 'a';
            if ((value >= 0 & value <= 9) || (alphaVal >= 0 && alphaVal <= 5))
                continue;
            return false;
        }
    }
}

std::string Line::getError() {
    return std::string();
}

int Line::getNextAddress(int locCtr) {
    if (equalsIgnoreCase(operation, "start")) {
        return std::stoi(operand, nullptr, 16);
    }else if(equalsIgnoreCase(operation, "end")){
        return locCtr;
    }
    if (!isValid()) {
        return locCtr;
    }
    OperationTable *opTable = OperationTable::getInstance();
    if (opTable->hasOperation(operation) || equalsIgnoreCase(operation, "word")) {
        return 3 + locCtr;
    } else if (equalsIgnoreCase(operation, "resw")) {
        return 3 * std::stoi(operand) + locCtr;
    } else if (equalsIgnoreCase(operation, "resb")) {
        return std::stoi(operand) + locCtr;
    } else if (equalsIgnoreCase(operation, "byte")) {
        return getConstSize() + locCtr;
    }
}

int Line::getConstSize() {
    char firstChar = tolower(operand[0]);
    if (firstChar == 'c')
        return operand.length() - 3;
    return (operand.length() - 3 + 1) / 2;
}
bool Line::equalsIgnoreCase(const std::string &str1, const char *str2) const {
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

bool Line::isEnd() const{
    return equalsIgnoreCase(operation, "end");
}