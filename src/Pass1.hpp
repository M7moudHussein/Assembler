#ifndef ASSEMBLER_PASS1_HPP
#define ASSEMBLER_PASS1_HPP

#include <string>
#include "SymbolTable.h"
#include "Line.h"

class Pass1 {
public:
    Pass1(std::string);
    std::string getInterFile();
    SymbolTable* getSymbolTable();
    int getProgramLength();
    int getStartingAddress();
    void printLisaFile();
    bool fail();

private:
    void compute();
    bool handleLine(Line , std::ofstream&);
    bool addLabel(std::string, int);

    const std::string INTER_FILE = "inter_file.txt";
    const std::string LISA_FILE = "lisa_file.txt";
    SymbolTable *symbolTable;
    std::string inputFile;
    int programLength, startingAddress, locCtr;

    std::string stringInput;
    bool hasError;
};


#endif //ASSEMBLER_PASS1_HPP
