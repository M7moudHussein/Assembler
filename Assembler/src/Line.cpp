/*
 * Line.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "Line.h"
#include "OperationTable.h"
#include <iostream>
#include <cstring>

Line::Line(std::string line) {
    parseLine(line);
}

Line::~Line() {

}

std::ostream &operator<<(std::ostream &os, const Line &line) {
    os << std::hex << line.address << std::dec << '\t' << line.label << '\t' << line.operation
       << '\t' << line.operand << '\t' << line.comment << '\n';
    return os;
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

bool Line::hasLabel() {
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

void Line::setAddress(int address) {
    this->address = address;
}

bool Line::isValid() {
    return true;
}

std::string Line::getError() {
    return std::string();
}

int Line::getNextAddress(int locCtr) {
    if (equalsIgnoreCase(operation, "start")) {
        return std::stoi(operand, nullptr, 16);
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

bool Line::equalsIgnoreCase(std::string &str1, const char *str2) {
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

int Line::getConstSize() {
    return 0;
}