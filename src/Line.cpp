#include <algorithm>
#include "Line.h"

void Line::parseLine(std::string line) {
    if (checkComment(line)) {
        _isComment = true;
        _comment = line;
    } else {
        std::vector<std::string> words = Util::split(line, '\t');
        if (words.size() < 3 || words.size() > 4) {
            _isFail = true;
            _errorMessage = "Invalid input format.";
        } else {
            _label = words[0];
            _operation = words[1];
            _operand = words[2];
            if (words.size() == 4)
                _comment = words[3];
        }
    }
}

bool Line::checkComment(std::string line) {
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '.')
            return true;
        if (isalpha(line[i]))
            return false;
    }
    return false;
}

void Line::checkData() {
    checkLabel() && checkOperation() && checkOperand();
}

bool Line::checkLabel() {
    if (hasLabel() && !validLabel(_label)) {
        _isFail = true;
        _errorMessage = "Invalid Label name\n";
        return false;
    }
    return true;
}

bool Line::checkOperation() {
    if (!hasOperation()) {
        _isFail = true;
        _errorMessage = _errorMessage + "No Operation Specified\n";
        return false;
    } else if ((!OperationTable::getInstance()->hasOperation(_operation)) && !checkDirective()) {
        _isFail = true;
        _errorMessage = _errorMessage + "Operation not in the Opt Table.\n";
        return false;
    }
    return true;
}

bool Line::checkOperand() {
    if (!hasOperand()) {
        _isFail = true;
        _errorMessage = _errorMessage + "No Operand Specified\n";
        return false;
    } else if (!validOperand(_operand)) {
        _isFail = true;
        _errorMessage = _errorMessage + "Operand is invalid.";
        return false;
    }
    return true;
}

bool Line::checkIndexedAddressing(){
    std::vector<std::string> vec = Util::split(_operand, ',');
    if(vec.size() != 2)
        return false;
    if((validLabel(vec[0]) || Util::validInteger(vec[0]))
        && (validLabel(vec[1]) || Util::validInteger(vec[1])))
        _isIndexed = true;
    return _isIndexed;
}

bool Line::validLabel(std::string label) const {
    bool firstLetter = false;
    for (int i = 0; i < label.length(); i++) {
        if (isalpha(label[i]))
            firstLetter = true;
        if ((!firstLetter) && (isspace(label[i]) ||
                               ((isalnum(label[i])) && (!isalpha(label[i])))))
            return false;
    }
    return true;
}

bool Line::validOperand(std::string operand) const {
    if(Util::hasCharacter(operand, ','))
        return checkIndexedAddressing();
    else
        return validLabel(operand) || Util::validInteger(operand);
}

int Line::getNextAddress() {
    if (Util::equalsIgnoreCase(_operation, "start")) {
        if (hasOperand())
            _address = std::to_string(std::stoi(_operand, nullptr, 16));
        else
            _address = "0";
        return getIntAddress();
    } else if (Util::equalsIgnoreCase(_operation, "end")) {
        _address = std::to_string(_locCtr);
        return _locCtr;
    }
    _address = std::to_string(_locCtr);
    if (fail()) {
        return _locCtr;
    }
    OperationTable *opTable = OperationTable::getInstance();
    if (opTable->hasOperation(_operation) || Util::equalsIgnoreCase(_operation, "word")) {
        return 3 + _locCtr;
    } else if (Util::equalsIgnoreCase(_operation, "resw")) {
        return 3 * std::stoi(_operand) + _locCtr;
    } else if (Util::equalsIgnoreCase(_operation, "resb")) {
        return std::stoi(_operand) + _locCtr;
    } else if (Util::equalsIgnoreCase(_operation, "byte")) {
        return Util::getConstSize(_operand) + _locCtr;
    }
    return -1;
}

bool Line::checkDirective() {
    if (Util::equalsIgnoreCase(_operation, "start") && hasOperand() && Util::validInteger(_operand))
        return true;
    else if (Util::equalsIgnoreCase(_operation, "end") && hasOperand() &&
             (Util::validInteger(_operand) || validLabel(_operand)))
        return true;
    else if ((Util::equalsIgnoreCase(_operation, "resw") || Util::equalsIgnoreCase(_operation, "resb"))
             && hasOperand() && Util::validInteger(_operand))
        return true;
    else if (Util::equalsIgnoreCase(_operation, "word") && hasOperand() && Util::validInteger(_operand))
        return true;
    else if (Util::equalsIgnoreCase(_operand, "byte") && hasOperand() &&
             Util::validByte(_operand) && Util::getConstSize(_operand))
        return true;
    return false;
}

std::string Line::getObjectCode(SymbolTable symbolTable) {
    std::stringstream objectCode;
    if (Util::equalsIgnoreCase(_operation, "RSUB")) {
        if (hasOperand()) {
            throw "RSUB must have no operand";
        }
        objectCode << buildCode("4C", std::string());
    } else if (Util::equalsIgnoreCase(_operation, "WORD")) {
        objectCode << buildCode(std::string(), Util::to_hexadecimal(_operand));
    } else if (Util::equalsIgnoreCase(_operation, "BYTE")) {
        std::string scannedCharacter = _operand.substr(2, _operand.length() - 3);
        if (tolower(_operand[0]) == 'c') {
            for (char ch: scannedCharacter)
                objectCode << Util::to_hexadecimal(ch);
        } else if (tolower(_operand[0]) == 'x') {
            objectCode << scannedCharacter;
        }
    } else if (Util::equalsIgnoreCase(_operation, "RESW") || Util::equalsIgnoreCase(_operation, "RESB")) {
        objectCode << std::string();
    } else {
        if (!OperationTable::getInstance()->hasOperation(_operation)) {
            throw "Operation Code Not Found!";
        } else if (!symbolTable.hasLabel(_operand)) {
            throw "Invalid operand no such a label!";
        }
        objectCode << buildCode(Util::to_hexadecimal(OperationTable::getInstance()->getOpCode(_operation)),
                                Util::to_hexadecimal(symbolTable.getAddress(_operand)));
    }
    return objectCode.str();
}

std::string Line::buildCode(std::string opCode, std::string labelCode) {
    while (opCode.length() < 2) {
        opCode = "0" + opCode;
    }
    while (labelCode.length() < 4) {
        labelCode = "0" + labelCode;
    }
    std::string ret = opCode + labelCode;
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}
