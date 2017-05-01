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

    bool addLabel(std::string, int);

    SymbolTable *symbolTable;
    std::string inputFile;
    int programLength, startingAddress;
    const std::string INTER_FILE = "inter_file.txt";

};

#endif /* MACHINE_H_ */
