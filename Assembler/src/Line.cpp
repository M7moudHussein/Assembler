/*
 * Line.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "Line.h"

Line::Line(std::string line) {
	parseLine(line);
}

Line::~Line() {

}

void Line::parseLine(std::string line){
    ReadState state = ReadState::LABEL;
    int pos = 0;
    int len = line.length();
    while(pos < len){
        char curChar = line[pos];
        if(isspace(curChar)){
            state = getNextState(state);
            while(pos < len - 1 && isspace(line[pos + 1])) pos++;
            continue;
        }
        switch(state){
            case ReadState::LABEL:
                label += curChar;
                readLabel = true;
                break;
            case ReadState::OPERATION:
                operation += curChar;
                readOperation = true;
                break;
            case ReadState::OPERAND:
                operand += curChar;
                readOperand = true;
                break;
            case ReadState::COMMENT:
                for(; pos < len; pos++)
                    comment += line[pos];
                readComment = true;
        }
    }
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