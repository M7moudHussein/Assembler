#ifndef ASSEMBLER_PASS1_HPP
#define ASSEMBLER_PASS1_HPP

#include <string>
#include "SymbolTable.h"
#include "Line.h"

/**
 * Class which is used to encapsulate the process of
 * Pass1 from the two Pass assembler. After processing
 * the First Pass, You must use the fail() to check
 * whether the process failed or not and whether it's
 * valid to start pass2 or not.
 */
class Pass1 {
public:
    /**
     * Constructor which takes as an input the name
     * of the input file from which the SIC code is
     * read.
     */
    Pass1(std::string);

    /**
     * @return the name of the Intermediate file
     * to be used by the second Pass.
     */
    std::string getInterFile();

    /**
     * @return the Symbol table which was built through
     * Pass1 to be used at Pass2 to identify the address
     * of the labels.
     */
    SymbolTable* getSymbolTable();

    /**
     * @return the length of the program.
     */
    int getProgramLength();

    /**
     * @return the starting address of the SIC program
     */
    int getStartingAddress();

    /**
     * Verify the state of the first pass
     * @return true in case of successiding in the first pass.
     */
    bool fail();

private:

    /**
     * Generates the intermediate file to be used by
     * the second pass.
     */
    void compute();

    /**
     * Handles a SIC line of code.
     * @return returns false if the Line of code contains
     * any Syntax error
     */
    bool handleLine(Line, std::string&);

    /**
     * Used to print the data accompanied in the symbol
     * table in the intermediate file to save the labels
     * with their relevant addresses to be used in the
     * second pass of the two pass assembler where it's
     * read in the begining of the second pass.
     */
    void printSymbolTable(std::ofstream&);

    /**
     * Adds a label to the Symbol table along
     * with its relevant address
     * @return true in case the label isn't a duplicate
     * and false in case it exists in the table.
     */
    bool addLabel(std::string, int);

    /**
     * The Function checks if a Line isn't needed to be
     * printed in the intermediate file as in case of
     * ORG, EQU or comments.
     * @return true in case of ORG, EQU, comments.
     */
    bool isExtraLine(Line);

    const std::string INTER_FILE = "inter_file.txt";
    SymbolTable *symbolTable;
    std::string _inputFile;
    int _programLength, _startingAddress, _locCtr;

    bool _hasError;
};


#endif //ASSEMBLER_PASS1_HPP
