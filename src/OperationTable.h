/*
 * OperationTable.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef OPERATIONTABLE_H_
#define OPERATIONTABLE_H_

#include "OpInfo.h"
#include <unordered_map>
#include <string>

/**
 * A table class used to read from file during the
 * initialization of the program the operations supported
 * by the machine and their relevant operation code.
 * It's also represented using a singleton as There's no
 * need for other than one machine.
 */
class OperationTable {
public:
	static OperationTable *getInstance();

	/**
	 * @param inst a string representing an instruction.
	 * @return returns true in case of containing the instruction name
	 * in the table.
	 * In case of not containing the instruction it returns the c++
	 * default initialization value which is '0'.
	 */
    bool hasOperation(std::string inst);

	/**
	 * @param inst a string representing an instruction.
	 * @return the format of the specified instruction.
	 */
	int getFormat(std::string inst);

	/**
	 * @param inst a string representing an instruction.
	 * @return the operation code for this specified instruction.
	 * In case of not containing the instruction it returns the c++
	 * default initialization value which is '0'.
	 */
    int getOpCode(std::string inst);


private:
	/**
	 * unordered_map which acts as a hashing based dictionary
	 * that contains the operations and the info assisted with them.
	 */
	std::unordered_map<std::string, OpInfo*> opTable;
	/**
	 * The name of the file containing the instructions.
	 */
    const char* INSTRUCTION_FILE = "data/instructions.txt";
    static OperationTable *instance;

    OperationTable();
    virtual ~OperationTable();
    void buildTable();
};
#endif /* OPERATIONTABLE_H_ */
