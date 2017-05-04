#ifndef MACHINE_H_
#define MACHINE_H_

#include "SymbolTable.h"
#include "Pass1.hpp"
#include "Pass2.hpp"
#include <string>


class Machine {
public:
    Machine(std::string, std::string);
    virtual ~Machine();
    void assemble();

private:
    std::string inputFile, outputFile;
};

#endif /* MACHINE_H_ */
