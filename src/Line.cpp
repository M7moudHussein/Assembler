
#include "Line.h"
#include "OperationTable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
Line::Line(std::string line) {
    parseLine(line);
}

Line::Line(){

}

Line::~Line() {

}

std::ostream &operator<<(std::ostream &os, const Line &line) {
    os << line.getHexAddress() << "\t";
    os << line.getLabel() << '\t'
       << line.getOperation() << '\t'
       << line.getOperand()  << '\t'
       << line.getComment();
    return os;
}

std::istream& operator >> (std::istream& is, Line& c)
{
    std::string input;
    getline(is, input);
    std::vector<std::string> args = c.split(input, '\t');
    c.address = args[0] == " " ? " " : std::to_string(stoi(args[0], nullptr, 16));
    c.label = args[1];
    c.operation = args[2];
    c.operand = args[3];
    c.comment = args[4];
    return is;
}

std::vector<std::string> Line::split(std::string input, char breaker) const{
    std::vector<std::string> result;
    std::string curStr;
    for(int i = 0; i < input.length(); i++){
        curStr += input[i];
        if(i + 1 < input.length() && input[i + 1] == breaker){
            result.push_back(curStr);
            while(i + 1 < input.length() && input[i + 1] == breaker) i++;
            curStr = std::string();
        }
    }
    result.push_back(curStr);
    return result;
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
                pos++;
                break;
            case ReadState::OPERATION:
                operation += curChar;
                pos++;
                break;
            case ReadState::OPERAND:
                operand += curChar;
                pos++;
                break;
            case ReadState::COMMENT:
                for (; pos < len; pos++)
                    comment += line[pos];
        }
    }
    reformData();
}

void Line::reformData() {
    if(label.length() == 0)
        label = " ";
    if(address.length() == 0)
        address = " ";
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

bool Line::hasAddress() const {
    return address != " ";
}

bool Line::hasLabel() const{
    return label != " ";
}

bool Line::hasOperand() const {
    return operand != " ";
}

bool Line::hasComment() const{
    return comment != " ";
}

std::string Line::getAddress() const {
    return address;
}

int Line::getIntAddress() const {
    if(!hasAddress())
        return -1;
    return std::stoi(address);
}

std::string Line::getHexAddress() const {
    if(!hasAddress())
        return " ";
    int dec = getIntAddress();
    std::stringstream ss;
    ss << std::hex << dec;
    return ss.str();
}

std::string Line::getLabel() const {
    return label;
}

std::string Line::getOperation() const{
    return operation;
}
std::string Line::getOperand() const {
    return operand;
}

std::string Line::getComment() const{
    return comment;
}

int Line::setAddress(int locCtr) {
    if (equalsIgnoreCase(operation, "start")) {
        if(hasOperand())
            address = std::to_string(std::stoi(operand, nullptr, 16));
        else
            address = "0";
        return getIntAddress();
    }else if(equalsIgnoreCase(operation, "end")){
        return locCtr;
    }
    address = std::to_string(locCtr);
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
