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
	 * The string data provided to the constructor is supposed
	 * to be a one line string which Contains the Label, Operation
	 * Operand and may contain a comment where they're separated
	 * by tabs and in case of missing argument it's replaced
	 * with a one space character.
	 */
	Line(std::string, int, SymbolTable*);

	virtual ~Line();

	/**
	 * Input and output stream operators are overloaded to ease
	 * printing and reading of the line code.
	 * In case of outputing the Line, It prints the Address of
	 * the line, follow by a Label, Operation, Operand, Object
	 * Code and they're separated by tabs an in case of a
	 * missing argument it's replaced by a single space character.
	 * Friend keyword is used to ease using the private data.
	 */
	friend std::ostream &operator<<(std::ostream &, const Line &);

	friend std::istream &operator>>(std::istream &is, Line &c);

	/**
	 * Functions checks the Line's Operation, location counter
	 * and data and upon thus returns the next address.
	 * The Next address depends on the current operation,
	 * where in case of Start, the Location counter doesn't
	 * change and in case of operations we add 3 bytes and
	 * in case of EQU, RESW, RESB,... It's dependant on the
	 * reserved size.
	 * @return the address of the next operation.
	 */
	int getNextAddress(SymbolTable*);

	/**
	 * Checks if the Line of code fails due to
	 * any syntax error as invalid input format not specifying
	 * the Tabs separation and existence of space in case of not
	 * having the required arguments.
	 *
	 */
	bool fail();

	/**
	 * In case of fail of the Line of code, It returns the error
	 * message specifying the first reason of failure only as
	 * It's useless to search for other errors when the syntax
	 * is already wrong which stops the whole program.
	 */
	std::string getError();

	/**
	 * Getters used to obtain the Label, Operation, Operand
	 * Comment or Object code of this line of code.
	 * In case of getObjectCode the object code is processed
	 * according to the operation and the label.
	 */
	std::string getLabel() const;

	std::string getOperation() const;

	std::string getOperand() const;

	std::string getComment() const;

	std::string getObjectCode(SymbolTable symbolTable);

	/**
	 * Returns the Index Label or value in case of
	 * Indexed addressing Mode.
	 * In case of checking Indexed, It checks for
	 * existence of a comma ',' and both labels on
	 * the two sides of the comma are valid labels
	 * or valid addresses.
	 */
	bool checkIndexed() const;

	std::string getIndexAddress() const;

	/**
	 * Returns the address of this line of code
	 * in an Integer form, string form or a base
	 * 16 string form.
	 * It's used also in printing the line where
	 * the address is the first argument printed.
	 * @return
	 */
	int getIntAddress() const;

	std::string getAddress() const;

	std::string getHexAddress() const;

	/**
	 * Checks whether the Line Has Label or not.
	 * Checks whether the Line has an operation or not
	 * Checks whether the Line has an operand or not
	 * In case of having a label equals to one space
	 * character, it's considered as not having label
	 * that's why when the user wants to avoid setting
	 * label for a line of code, he uses a space character
	 * instead.
	 * @return
	 */
	bool hasLabel() const;

	bool hasOperation() const;

	bool hasOperand() const;

	/**
	 * Checks whether this Line is the Start line,
	 * End Line by comparing the Directive keyword
	 * using EqualsIgnoreCase to the keywords 'start'
	 * and 'end'
	 * The check for the Comment follows a different
	 * procedure by checking the first character
	 * whether it's a dot '.' or not.
	 */
	bool isStart() const;

	bool isComment() const;

	bool isEnd() const;

    bool isEQU() const;

    bool isORG() const;

private:
	std::string _address, _extraAddress, _label, _operation, _operand, _comment;
	std::string _errorMessage;
	int _locCtr;

	bool _isComment, _isFail, _isIndexed;

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
	bool checkData(SymbolTable*);
	bool checkLabel();
	bool checkOperation(SymbolTable*);
	bool checkDirective(SymbolTable*);


	/**
	 * Takes an operation code with label to built the output
	 * as an Obj code.
	 * @param opCode
	 * @param labelCode
	 * @return	string specifying the operation code and label code
	 */
	std::string buildCode(std::string opCode, std::string labelCode);

	std::string stringToHexadecimal(std::string);
};

#endif /* LINE_H_ */
