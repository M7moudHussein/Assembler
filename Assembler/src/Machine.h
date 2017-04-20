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
    std::string pass1(std::string);

    std::vector<std::string> parseLine(std::string &line);

    void pass2(std::string);

    bool addLabel(std::string, int);

    std::string getProgramLength(std::string line);

    std::string to_hexadecimal(std::string number);

    SymbolTable *symbolTable;
    std::string inputFile;

    SymbolTable *readIntermediateFile(std::string intermedFile);
};

#endif /* MACHINE_H_ */
