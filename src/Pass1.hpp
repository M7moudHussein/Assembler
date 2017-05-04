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
    std::vector<Line> getProgramCode();

private:
    void compute();
    bool handleLine(Line , std::ofstream&);
    bool addLabel(std::string, int);

    const std::string INTER_FILE = "inter_file.txt";
    const std::string LISA_FILE = "lisa_file.txt";
    SymbolTable *symbolTable;
    std::string _inputFile;
    int _programLength, _startingAddress, _locCtr;
    std::vector<Line> _programCode;

    std::string _stringInput;
    bool _hasError;
};


#endif //ASSEMBLER_PASS1_HPP
