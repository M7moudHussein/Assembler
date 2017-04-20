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
	int pass1(std::string);
	void pass2();
	SymbolTable* readIntermediateFile();
	bool addLabel(std::string, int);

	SymbolTable* symbolTable;
	std::string inputFile;
	int programLength, startingAddress;
	const std::string INTER_FILE = "inter_file.txt";

    std::vector<std::string> parseLine(std::string &line);

    void pass2(std::string);


    std::string getProgramLength(std::string line);

    std::string to_hexadecimal(std::string number);


    SymbolTable *readIntermediateFile(std::string intermedFile);
};

#endif /* MACHINE_H_ */
