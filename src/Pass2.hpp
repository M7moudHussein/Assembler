#ifndef ASSEMBLER_PASS2_HPP
#define ASSEMBLER_PASS2_HPP

#include "SymbolTable.h"
#include <string>
#include "Line.h"
#include "Util.hpp"
#include "TextRecord.h"
#include "fstream"

class Pass2 {
public:
    Pass2(SymbolTable*, std::string, int);
    void generateObjFile(std::string);
private:
    void compute(std::string);
    std::string _interFile;
    int _programLength;
    SymbolTable* symbolTable;
};


#endif //ASSEMBLER_PASS2_HPP
