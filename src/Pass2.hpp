#ifndef ASSEMBLER_PASS2_HPP
#define ASSEMBLER_PASS2_HPP

#include "SymbolTable.h"
#include <string>
#include "Line.h"
#include "Util.hpp"
#include "TextRecord.h"
#include "fstream"

/**
 * Class used to encapsulate the process of
 * the second Pass of the two pass assembler.
 */
class Pass2 {
public:

	/**
	 * Constructor which takes the Symbol table
	 * and the name of the intermediate file and the
	 * value that specifies the length of the program.
	 */
	Pass2(std::string, int);

	/**
	 * Public Linker function to generate the object
	 * code.
	 */
	void generateObjFile(std::string, std::string);

private:

	/**
	 * Generates the object code for the intermediate file
	 * specified by the first string and uses the second
	 * string as a name for the output file.
	 */
	void compute(std::string, std::string);

	/**
	 * Initialise the symbol table with the data that had
	 * been taken from the first pass and sets a new symbol
	 * table to be used in the second pass.
	 */
	void initSymbolTable(std::string);
	/**
	 * @return a Header specified by the Line and the Address specified
	 */
	std::string buildHeader(Line, std::string &);

	/**
	 * @return Using the start address, it builts the End
	 */
	std::string buildEnd(std::string startAddress);

	std::string _interFile;
	int _programLength;
	SymbolTable *symbolTable;
	std::vector<Line> programCode;
};


#endif //ASSEMBLER_PASS2_HPP
