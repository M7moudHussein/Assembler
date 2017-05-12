#include "Line.h"
#include <string>

Line::Line(std::string line, int locCtr, SymbolTable* symbolTable) : _locCtr(locCtr) {
    _isFail = false;
    _isComment = false;
    _isIndexed = false;
    parseLine(line);
    if ((!_isComment)) {
        checkData(symbolTable);
        getNextAddress(symbolTable);
    }
}

Line::Line() {
    _isFail = false;
    _isComment = false;
    _isIndexed = false;
}

Line::~Line() {
}

std::ostream &operator<<(std::ostream &os, const Line &line) {
    if (line.isComment())
        os << line.getComment();
    else {
        os << line.getHexAddress() << "\t";
        os << line.getLabel() << '\t'
           << line.getOperation() << '\t'
           << line.getOperand();
        if(line.checkIndexed()) {
            os << "," << line.getIndexAddress();
        }
        os  << '\t'
           << line.getComment();
    }
    return os;
}

std::istream &operator>>(std::istream &is, Line &c) {
    std::string input;
    getline(is, input);
    std::vector<std::string> args = Util::split(input, '\t');
    c._address = args[0] == " " ? " " : std::to_string(stoi(args[0], nullptr, 16));
    c._label = args[1];
    c._operation = args[2];
    c._operand = args[3];
    c._comment = args[4];
    if(Util::validIndexed(c._operand)){
        c._isIndexed = true;
        std::vector<std::string> vec = Util::split(c._operand, ',');
        c._operand = vec[0];
        c._extraAddress = vec[1];
    }
    return is;
}

bool Line::hasLabel() const {
    return _label != " ";
}

bool Line::hasOperation() const {
    return _operation != " ";
}

bool Line::hasOperand() const {
    return _operand != " ";
}


std::string Line::getAddress() const {
    return _address;
}

int Line::getIntAddress() const {
    return std::stoi(_address);
}

std::string Line::getHexAddress() const {
    int dec = getIntAddress();
    std::stringstream ss;
    ss << std::hex << dec;
    return ss.str();
}

std::string Line::getLabel() const {
    return _label;
}

std::string Line::getOperation() const {
    return _operation;
}

std::string Line::getOperand() const {
    return _operand;
}

bool Line::checkIndexed() const {
    return _isIndexed;
}

std::string Line::getIndexAddress() const{
    if(_isIndexed)
        return _extraAddress;
    return "0";
}

std::string Line::getComment() const {
    if(_comment == "")
        return " ";
    return _comment;
}

bool Line::fail() {
    return _isFail;
}

std::string Line::getError() {
    return _errorMessage;
}

bool Line::isStart() const {
    return Util::equalsIgnoreCase(_operation, "start");
}

bool Line::isComment() const {
    return _isComment;
}

bool Line::isEnd() const {
    return Util::equalsIgnoreCase(_operation, "end");
}

bool Line::isEQU() const {
    return Util::equalsIgnoreCase(_operation, "equ");
}

bool Line::isORG() const {
    return Util::equalsIgnoreCase(_operation, "org");
}