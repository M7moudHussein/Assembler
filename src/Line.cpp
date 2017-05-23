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

bool Line::checkData(SymbolTable *symbolTable) {
	return checkLabel() && checkOperation(symbolTable);
}

bool Line::checkLabel() {
	if (hasLabel() && !Util::validLabel(_label)) {
		_isFail = true;
		_errorMessage = "Invalid Label name, Please Choose anther one.";
		return false;
	}
	return true;
}

bool Line::checkOperation(SymbolTable *symbolTable) {
	if (Util::isDirective(_operation)) {
		return checkDirective(symbolTable);
	} else if (OperationTable::getInstance()->hasOperation(_operation)) {
		if (hasOperand() && _operand.length() != 0 && _operand[0] == '=') {
			if (!Util::validLiteral(_operand)) {
				_isFail = true;
				_errorMessage = "Invalid Literal Used";
				return false;
			}
			_hasLiteral = true;
			return true;
		} else if (Util::validIndexed(_operand)) {
			_isIndexed = true;
			std::vector<std::string> vec = Util::split(_operand, ',');
			_operand = vec[0];
			_extraAddress = vec[1];
			return true;
		} else if (!hasOperand()) {
			if (Util::equalsIgnoreCase(_operation, "rsub"))
				return true;
			_isFail = true;
			_errorMessage = "Missing Operand for this operation.";
		} else if (hasOperand() && !Util::validOperand(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Operand Specified, Please recheck this operand.";
		}
		return true;
	}
	return false;
}

bool Line::checkDirective(SymbolTable *symbolTable) {
	if (Util::equalsIgnoreCase(_operation, "start")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing Starting Address.";
			return false;
		} else if (!Util::validHexa(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Starting Address";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "end")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing End Address";
			return false;
		} else if (!Util::validOperand(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Ending Address/Label.";
			return false;
		}
	} else if (Util::equalsIgnoreCase(_operation, "resw")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing word array size";
			return false;
		} else if (!Util::validInteger(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Size Specified";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "resb")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing byte array size";
			return false;
		} else if (!Util::validInteger(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Size Specified";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "byte")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing Data.";
			return false;
		} else if (!Util::validByte(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Byte Specified.";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "word")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing Data";
			return false;
		} else if (!Util::validHexaArray(_operand)) {
			_isFail = true;
			_errorMessage = "Invalid Integer Array defined.";
			return false;
		}
		if (Util::split(_operand, ',').size() > 10) {
			_isFail = true;
			_errorMessage = "Large number of words in the array";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "equ")) {
		if (!hasOperand()) {
			_isFail = true;
			_errorMessage = "Missing Mathematical Expression.";
			return false;
		} else if (!Util::validMathExpression(_operand, symbolTable)) {
			_isFail = true;
			_errorMessage = "Invalid Mathematical Expression.";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "org")) {
		if (!Util::validMathExpression(_operand, symbolTable)) {
			_isFail = true;
			_errorMessage = "Invalid Mathematical Expression.";
			return false;
		}
		return true;
	} else if (Util::equalsIgnoreCase(_operation, "ltorg")) {
		if (hasOperand() || hasLabel()) {
			_isFail = true;
			_errorMessage = "Such directive can't have a label nor an operand";
			return false;
		}
		return true;
	}
	return false;
}


int Line::getNextAddress(SymbolTable *symbolTable) {
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
	if (Util::equalsIgnoreCase(_operation, "ltorg"))
		return _locCtr;
	if (fail()) {
		return _locCtr;
	}
	OperationTable *opTable = OperationTable::getInstance();
	if (opTable->hasOperation(_operation)) {
		return 3 + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "word")) {
		return 3 * (Util::split(_operand, ',').size()) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "resw")) {
		return 3 * std::stoi(_operand) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "resb")) {
		return std::stoi(_operand) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "byte")) {
		return Util::getConstSize(_operand) + _locCtr;
	} else if (Util::equalsIgnoreCase(_operation, "equ") || Util::equalsIgnoreCase(_operation, "org")) {
		return Util::evalMathExpression(_operand, symbolTable, _locCtr);
	}
	return -1;
}

std::string Line::getObjectCode(SymbolTable &symbolTable, LiteralTable &literalTable) {
	std::stringstream objectCode;
	if (Util::equalsIgnoreCase(_operation, "RSUB")) objectCode << buildCode("4C", std::string());
	else if (Util::equalsIgnoreCase(_operation, "WORD")) { return handleWordObjectCode(_operand); }
	else if (Util::equalsIgnoreCase(_operation, "BYTE")) {
		std::string scannedString = _operand.substr(2, _operand.length() - 3);
		if (Util::equalsIgnoreCase(_operand[0], 'C')) { objectCode << stringToHexadecimal(scannedString); }
		else if (Util::equalsIgnoreCase(_operand[0], 'X')) { objectCode << scannedString; }
	} else if (Util::equalsIgnoreCase(_operation, "RESW") || Util::equalsIgnoreCase(_operation, "RESB")) {
		objectCode << std::string();
	} else {
		std::string opCode = Util::to_hexadecimal(OperationTable::getInstance()->getOpCode(_operation));
		std::string labelCode;
		if ((!Util::validHexa(_operand)) && !symbolTable.hasLabel(_operand)) {
			std::cout << _operation << " " << _operand << std::endl;
			throw "Invalid Operand..No Such A Label!";
		} else if (_hasLiteral) {
			objectCode << literalTable.getAddress(_operand[1], _operand.substr(3, _operand.length() - 4));
		} else if (!Util::validHexa(_operand)) {
			labelCode = Util::to_hexadecimal(symbolTable.getAddress(_operand) + (_isIndexed ? 0x8000 : 0));
		} else { labelCode = _operand; }
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

std::string Line::handleWordObjectCode(std::string operand) {
	std::vector<std::string> vec = Util::split(operand, ',');
	std::string objectCode;
	for (unsigned int i = 0; i < vec.size(); i++) {
		objectCode.append(buildCode(std::string(), Util::to_hexadecimal(vec[i])));
		if (i < vec.size() - 1) {
			objectCode.append(Util::SEPARATOR);
		}
	}
	return objectCode;
}
