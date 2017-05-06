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
    if (hasLabel() && (!Util::validLabel(_label))) {
        _isFail = true;
        _errorMessage = "Invalid Label specified";
    } else if ((!hasOperation())) {
        _isFail = true;
        _errorMessage = "Unspecified Operation.";
    } else if ((!Util::isDirective(_operation)) && (!Util::validOperation(_operation))) {
        _isFail = true;
        _errorMessage = "The specified operation is invalid";
    } else {
        if (Util::isDirective(_operation))
            _isDirective = true;
        if (Util::hasCharacter(_operand, ','))
            _isIndexed = true;
        if (_isIndexed && (!Util::validIndexed(_operand))) {
            _isFail = true;
            _errorMessage = "Wrong Usage of Indexed Mode";
        } else if (!Util::validOperand(_operand)) {
            _isFail = true;
            _errorMessage = "Invalid Operand used";
        }
        if (_isIndexed && (!_isFail)) {
            std::vector<std::string> vec = Util::split(_operand, ',');
            _operand = vec[0];
            _extraAddress = vec[1];
        }
    }
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

/**
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
*/

std::string Line::getObjectCode(SymbolTable symbolTable) {
    std::stringstream objectCode;
    if (Util::equalsIgnoreCase(_operation, "RSUB")) {
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
        if (!symbolTable.hasLabel(_operand)) {
            throw "Invalid Operand..No Such A Label!";
        }
        std::string opCode = Util::to_hexadecimal(OperationTable::getInstance()->getOpCode(_operation));
        std::string labelCode = Util::to_hexadecimal(symbolTable.getAddress(_operand) + _isIndexed ? 8000 : 0);
        objectCode << buildCode(opCode, labelCode);
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