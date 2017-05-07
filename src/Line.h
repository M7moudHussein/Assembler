#ifndef LINE_H_
#define LINE_H_

#include <string>
#include <vector>
#include "OperationTable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include "Util.hpp"
#include "SymbolTable.h"

/**
 * Class encapsulating the Line of SIC code
 * It contains the process of parsing and evaluating
 * and the generation of the object code for the line.
 */
class Line {
public:

	/**
	 * Constructors for the Line used as a copy constructor
	 */
	Line();

	/**
	 * Constructor for the Line that takes a line of input
	 * and a Location counter to generate the relevant data.
	 */
	Line(std::string, int);
	virtual ~Line();

	/**
	 * Input and output stream operators are overloaded to ease
	 * printing and reading of the line code.
	 * Friend keyword is used to ease using the private data.
	 */
	friend std::ostream &operator<<(std::ostream &, const Line &);
	friend std::istream &operator>>(std::istream &is, Line &c);

	/**
	 * Functions checks the Line's Operation, location counter
	 * and data and upon thus returns the next address.
	 * @return the address of the next operation.
	 */
	int getNextAddress();

	/**
	 * Checks if the Line of code fails due to
	 * any syntax error as invalid input format not specifying
	 * the Tabs separation and existance of space in case of not
	 * having the required arguments.
	 */
	bool fail();

	/**
	 * In case of fail of the Line of code, It returns the error
	 * message specifying the first reason of failure.
	 */
	std::string getError();

	/**
	 * Getters used to obtain the Label, Operation, Operand
	 * Comment or Object code of this line of code.
	 */
	std::string getLabel() const;
	std::string getOperation() const;
	std::string getOperand() const;
	std::string getComment() const;
	std::string getObjectCode(SymbolTable symbolTable);

	/**
	 * Returns the Index Label or value in case of
	 * Indexed addressing Mode.
	 */
	bool checkIndexed() const;
	std::string getIndexAddress() const;

	/**
	 * Returns the address of this line of code
	 * in an Integer form, string form or a base
	 * 16 string form.
	 * @return
	 */
	int getIntAddress() const;
	std::string getAddress() const;
	std::string getHexAddress() const;

	/**
	 * Checks whether the Line Has Label or not.
	 * Checks whether the Line has an operation or not
	 * Checks whether the Line has an operand or not
	 * @return
	 */
	bool hasLabel() const;
	bool hasOperation() const;
	bool hasOperand() const;

	/**
	 * Checks whether this Line is the Start line,
	 * End Line or a Comment Line.
	 */
	bool isStart() const;
	bool isComment() const;
	bool isEnd() const;

private:
	std::string _address, _extraAddress, _label, _operation, _operand, _comment;
	std::string _errorMessage;
	int _locCtr;

	bool _isComment, _isFail, _isIndexed, _isDirective;

	/**
	 * Parses a line of inputs to generate the data of the
	 * Line object.
	 * @param line is a line of input given by the user.
	 */
	void parseLine(std::string line);

	/**
	 * Checks whether this input specified a comment or not.
	 * @return true in case of making a comment
	 */
	bool checkComment(std::string);

	/**
	 * Checks the data of the Code
	 * As of Label,Operation, Operand and Comment
	 * to validate the four of them.
	 */
	void checkData();

	/**
	 * Takes an operation code with label to built the output
	 * as an Obj code.
	 * @param opCode
	 * @param labelCode
	 * @return	string specifying the operation code and label code
	 */
	std::string buildCode(std::string opCode, std::string labelCode);
};

#endif /* LINE_H_ */
