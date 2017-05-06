#ifndef LINE_H_
#define LINE_H_

#include <string>
#include <vector>
#include "OperationTable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include "Util.hpp"
#include "SymbolTable.h"

class Line {
public:
	Line();

	Line(std::string, int);

	virtual ~Line();

	friend std::ostream &operator<<(std::ostream &, const Line &);

	friend std::istream &operator>>(std::istream &is, Line &c);

	int getNextAddress();

	bool fail();

	std::string getError();

	std::string getLabel() const;

	std::string getOperation() const;

	std::string getOperand() const;

	std::string getIndexAddress() const;

	std::string getComment() const;

	bool hasLabel() const;

	bool hasOperation() const;

	bool hasOperand() const;

	int getIntAddress() const;

	std::string getAddress() const;

	std::string getHexAddress() const;

	std::string getObjectCode();

	bool isStart() const;

	bool isComment() const;

	bool isEnd() const;


	std::string getObjectCode(SymbolTable symbolTable);

private:
	std::string _address, _extraAddress, _label, _operation, _operand, _comment;
	std::string _nextAddress, _errorMessage;
	int _locCtr;

	bool _isComment, _isFail, _isIndexed, _isDirective;

	void parseLine(std::string line);

	bool checkComment(std::string);

	void checkData();

	std::string buildCode(std::string opCode, std::string labelCode);

};

#endif /* LINE_H_ */
