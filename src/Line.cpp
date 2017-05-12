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
			if (words.size() > 3)
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

bool Line::checkData(SymbolTable* symbolTable) {
    return checkLabel() && checkOperation(symbolTable);
}

bool Line::checkLabel(){
    if(hasLabel() && !Util::validLabel(_label)){
        _isFail = true;
        _errorMessage = "Invalid Label name, Please Choose anther one.";
        return false;
    }
    return true;
}

bool Line::checkOperation(SymbolTable* symbolTable){
    if(Util::isDirective(_operation)) {
        return checkDirective(symbolTable);
    }
    else if(OperationTable::getInstance()->hasOperation(_operation)){
        if(Util::validIndexed(_operand)){
            _isIndexed = true;
            std::vector<std::string> vec = Util::split(_operand, ',');
            _operand = vec[0];
            _extraAddress = vec[1];
            return true;
        }else if(!hasOperand()){
          if(Util::equalsIgnoreCase(_operation, "rsub"))
              return true;
            _isFail = true;
            _errorMessage = "Missing Operand for this operation.";
        } else if(hasOperand() && !Util::validOperand(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Operand Specified, Please recheck this operand.";
        }
        return true;
    }
    return false;
}

bool Line::checkDirective(SymbolTable* symbolTable){
    if(Util::equalsIgnoreCase(_operation, "start")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing Starting Address.";
        }else if(!Util::validHexa(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Starting Address";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "end")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing End Address";
        }else if(!Util::validOperand(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Ending Address/Label.";
        }
    }else if(Util::equalsIgnoreCase(_operation, "resw")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing word array size";
        }else if(!Util::validInteger(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Size Specified";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "resb")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing byte array size";
        }else if(!Util::validInteger(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Size Specified";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "byte")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing Data.";
        }else if(!Util::validByte(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Byte Specified.";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "word")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing Data";
        }else if(!Util::validHexaArray(_operand)){
            _isFail = true;
            _errorMessage = "Invalid Integer Array defined.";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "equ")){
        if(!hasOperand()){
            _isFail = true;
            _errorMessage = "Missing Mathematical Expression.";
        }else if(!Util::validMathExpression(_operand, symbolTable)){
            _isFail = true;
            _errorMessage = "Invalid Mathematical Expression.";
        }
        return true;
    }else if(Util::equalsIgnoreCase(_operation, "org")) {
        if(hasOperand()){
            _isFail = true;
            _errorMessage = "Such operatin can't have an operand.";
        }else if(!Util::validMathExpression(_operand, symbolTable)){
            _isFail = true;
            _errorMessage = "Invalid Mathematical Expression.";
        }
        return true;
    }
    return false;
}


int Line::getNextAddress(SymbolTable* symbolTable) {
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
	if (opTable->hasOperation(_operation)){
		return 3 + _locCtr;
	} else if(Util::equalsIgnoreCase(_operation, "word")){
		return 3 * (Util::split(_operand, ',').size()) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "resw")) {
		return 3 * std::stoi(_operand) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "resb")) {
		return std::stoi(_operand) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "byte")) {
		return Util::getConstSize(_operand) + _locCtr;
	}else if(Util::equalsIgnoreCase(_operation, "equ") || Util::equalsIgnoreCase(_operation, "org")){
        return Util::evalMathExpression(_operand, symbolTable);
	}
	return -1;
}

std::string Line::getObjectCode(SymbolTable symbolTable) {
	std::stringstream objectCode;
	if (Util::equalsIgnoreCase(_operation, "RSUB")) {
		objectCode << buildCode("4C", std::string());
	} else if (Util::equalsIgnoreCase(_operation, "WORD")) {
        // TODO
        // 7sen 3adl dy
		objectCode << buildCode(std::string(), "NAN");
	} else if (Util::equalsIgnoreCase(_operation, "BYTE")) {
		std::string scannedString = _operand.substr(2, _operand.length() - 3);
		if (tolower(_operand[0]) == 'c') {
			objectCode << stringToHexadecimal(scannedString);
		} else if (tolower(_operand[0]) == 'x') {
			objectCode << scannedString;
		}
	} else if (Util::equalsIgnoreCase(_operation, "RESW") || Util::equalsIgnoreCase(_operation, "RESB")) {
		objectCode << std::string();
	} else {
		if ((!Util::validHexa(_operand)) && !symbolTable.hasLabel(_operand)) {
            std::cout << _operation << " " << _operand << std::endl;
			throw "Invalid Operand..No Such A Label!";
		}
		std::string opCode = Util::to_hexadecimal(OperationTable::getInstance()->getOpCode(_operation));
		std::string labelCode;
        if(!Util::validHexa(_operand))
            labelCode = Util::to_hexadecimal(symbolTable.getAddress(_operand) + (_isIndexed ? 0x8000 : 0));
        else
            labelCode = _operand;
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

std::string Line::stringToHexadecimal(std::string string) {
	std::string ret;
	for (char ch: string) {
		ret.append(Util::to_hexadecimal(ch));
	}
	std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
	return ret;
}
