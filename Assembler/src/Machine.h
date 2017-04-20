/*
 * Machine.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#include "SymbolTable.h"
#include <string>

enum class ProgramState{ START, PROGRAM, END};

class Machine {
public:
	Machine(std::string);
	virtual ~Machine();
	void assemble();

private:
	int pass1(std::string);
	void pass2();
	SymbolTable* readIntermediateFile();
	bool addLabel(std::string, int);

	SymbolTable* symbolTable;
	std::string inputFile;
	int programLength, startingAddress;
	const std::string INTER_FILE = "inter_file.txt";
};

#endif /* MACHINE_H_ */
