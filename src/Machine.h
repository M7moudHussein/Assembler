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
#include <vector>

enum class ProgramState {
    START, PROGRAM, END
};

class Machine {
public:
    Machine(std::string);

    virtual ~Machine();

    void assemble();

private:


	SymbolTable* symbolTable;
	std::string inputFile;
	int programLength, startingAddress;
	const std::string INTER_FILE = "inter_file.txt";

    std::vector<std::string> parseLine(std::string &line);


	int pass1(std::string);
	void pass2();
	bool addLabel(std::string, int);
    std::string to_hexadecimal(std::string number);
};

#endif /* MACHINE_H_ */
