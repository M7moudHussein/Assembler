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
	Pass2(SymbolTable *, std::string, int, std::vector<Line>);

	void generateObjFile(std::string);

private:
	void compute(std::string);

	std::string _interFile;
	int _programLength;
	SymbolTable *symbolTable;
	std::vector<Line> programCode;
	std::string buildHeader(Line line, std::string &startAddress);

	std::string buildEnd(std::string startAddress);
};


#endif //ASSEMBLER_PASS2_HPP
