#include "Line.h"


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
    std::vector<std::string> args = Util::split(input, '\t');
    c.address = args[0] == " " ? " " : std::to_string(stoi(args[0], nullptr, 16));
    c.label = args[1];
    c.operation = args[2];
    c.operand = args[3];
    c.comment = args[4];
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
            while (pos < len && isspace(line[pos])) pos++;
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

std::string Line::getAddress() const {
    return address;
}

int Line::getIntAddress() const {
    return std::stoi(address);
}

std::string Line::getHexAddress() const {
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

int Line::getNextAddress()() {
    if (Util::equalsIgnoreCase(operation, "start")) {
        if(hasOperand())
            address = std::to_string(std::stoi(operand, nullptr, 16));
        else
            address = "0";
        return getIntAddress();
    }else if(Util::equalsIgnoreCase(operation, "end")){
        return locCtr;
    }
    address = std::to_string(locCtr);
    if (fail()) {
        return locCtr;
    }
    OperationTable *opTable = OperationTable::getInstance();
    if (opTable->hasOperation(operation) || Util::equalsIgnoreCase(operation, "word")) {
        return 3 + locCtr;
    } else if (Util::equalsIgnoreCase(operation, "resw")) {
        return 3 * std::stoi(operand) + locCtr;
    } else if (Util::equalsIgnoreCase(operation, "resb")) {
        return std::stoi(operand) + locCtr;
    } else if (Util::equalsIgnoreCase(operation, "byte")) {
        return Util::getConstSize(operand) + locCtr;
    }
}
bool Line::fail(){
    if(operation == "resw" || operation == "resb" || operation == "word")
        return Util::validInteger(operand);
    if(operation == "byte")
        return Util::validByte(operand);
    return true;
}


bool Line::isEnd() const{
    return Util::equalsIgnoreCase(operation, "end");
}
