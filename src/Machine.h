#ifndef MACHINE_H_
#define MACHINE_H_

#include "SymbolTable.h"
#include "Pass1.hpp"
#include "Pass2.hpp"
#include <string>

/**
 * Machine class which creates two objects, pass1 and pass2 objects,
 * Then uses them to generate the intermediate file and start pass2
 * in case of success else we stop pass2 from initialization.
 */
class Machine {
public:
    Machine(std::string);
    virtual ~Machine();
    /**
     * does the whole process of using the two passes to
     * create the object file data.
     * In case of failure of the first pass due to a
     * syntax error or such, then the second pass doesn't
     * go on.
     */
    void assemble();

private:
    std::string inputFile;
};

#endif /* MACHINE_H_ */
