#include "Line.h"

void Line::parseLine(std::string line) {
    if(checkComment(line)){
        _isComment = true;
        _comment = line;
    }else {
        std::vector<std::string> words = Util::split(line, '\t');
        if(words.size() < 3 || words.size() > 4){
            _isFail = true;
            _errorMessage = "Invalid input format.";
        }else{
            _label = words[0];
            _operation = words[1];
            _operand = words[2];
            if(words.size() == 4)
                _comment = words[3];
        }
    }
}

bool Line::checkComment(std::string line) {
    for(int i = 0; i < line.length(); i++){
        if(line[i] == '.')
            return true;
        if(isalpha(line[i]))
            return false;
    }
    return false;
}

void Line::checkData() {
    checkLabel() && checkOperation() && checkOperand();
}

bool Line::checkLabel() {
    if(hasLabel() && !validLabel(_label)){
        _isFail = true;
        _errorMessage = "Invalid Label name\n";
        return false;
    }
    return true;
}

bool Line::checkOperation() {
    if(!hasOperation()){
        _isFail = true;
        _errorMessage = _errorMessage + "No Operation Specified\n";
        return false;
    }else if((!OperationTable::getInstance()->hasOperation(_operation)) && !checkDirective()){
        _isFail = true;
        _errorMessage = _errorMessage + "Operation not in the Opt Table.\n";
        return false;
    }
    return true;
}

bool Line::checkOperand() {
    if(!hasOperand()){
        _isFail = true;
        _errorMessage = _errorMessage + "No Operand Specified\n";
        return false;
    }else if(!validOperand(_operand)){
        _isFail = true;
        _errorMessage = _errorMessage + "Operand is invalid.";
        return false;
    }
    return true;
}

bool Line::validLabel(std::string label) const{
    bool firstLetter = false;
    for(int i = 0; i < label.length(); i++){
        if(isalpha(label[i]))
            firstLetter = true;
        if((!firstLetter) && (isspace(label[i]) ||
                ((isalnum(label[i])) && (!isalpha(label[i])))))
            return false;
    }
    return true;
}

bool Line::validOperand(std::string operand) const{
    return validLabel(operand) || Util::validInteger(operand);
}

int Line::getNextAddress() {
    if (Util::equalsIgnoreCase(_operation, "start")) {
        if(hasOperand())
            _address = std::to_string(std::stoi(_operand, nullptr, 16));
        else
            _address = "0";
        return getIntAddress();
    }else if(Util::equalsIgnoreCase(_operation, "end")){
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

bool Line::checkDirective(){
    if(Util::equalsIgnoreCase(_operation, "start") && hasOperand() && Util::validInteger(_operand))
        return true;
    else if(Util::equalsIgnoreCase(_operation, "end") && hasOperand() &&
            (Util::validInteger(_operand) || validLabel(_operand)))
        return true;
    else if((Util::equalsIgnoreCase(_operation, "resw") || Util::equalsIgnoreCase(_operation,"resb"))
        &&  hasOperand() && Util::validInteger(_operand))
        return true;
    else if(Util::equalsIgnoreCase(_operation, "word") && hasOperand() && Util::validInteger(_operand))
        return true;
    else if(Util::equalsIgnoreCase(_operand, "byte") && hasOperand() &&
            Util::validByte(_operand) && Util::getConstSize(_operand))
        return true;
    return false;
}