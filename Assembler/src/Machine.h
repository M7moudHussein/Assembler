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

class Machine {
public:
	Machine(std::string);
	virtual ~Machine();
	void assemble();

private:
	std::string pass1(std::string);
	void pass2(std::string);
	SymbolTable* readIntermediateFile();

	SymbolTable* symbolTable;
	std::string inputFile;
};

#endif /* MACHINE_H_ */
