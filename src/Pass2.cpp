//
// Created by Mohamed Ayman on 5/3/2017.
//

#include "Pass2.hpp"

Pass2::Pass2(SymbolTable *symbolTable, std::string interFile, int programLength, std::vector<Line> programCode) :
		symbolTable(symbolTable), _interFile(interFile), _programLength(programLength), programCode(programCode) {
}

void Pass2::generateObjFile(std::string output) {
	compute(output);
}

void Pass2::compute(std::string output) {
	std::ofstream outputStream(output);
	TextRecord textRecord;
	std::string startAddress;
	for (Line line : programCode) {
		if (line.isStart()) {
			outputStream << buildHeader(line, startAddress) << std::endl;
			textRecord = TextRecord(startAddress);
		} else if (line.isEnd()) {
			if (!textRecord.empty()) {
				outputStream << textRecord << std::endl;
			}
			outputStream << buildEnd(startAddress) << std::endl;
			break;
		} else {
			std::string objectCode = line.getObjectCode(*symbolTable);
			if (!textRecord.fits(objectCode)) {
				outputStream << textRecord << std::endl;
				textRecord = TextRecord(Util::formalize(Util::to_hexadecimal(line.getAddress()), 6));
			}
			textRecord.append(objectCode);
		}
	}
	outputStream.close();
}

std::string Pass2::buildHeader(Line line, std::string &startAddress) {
	startAddress = line.getOperand();
	std::string ret;
	ret.append("H");
	ret.append(Util::SEPARATOR);
	ret.append(line.getLabel());
	ret.append("\t");
	ret.append(Util::SEPARATOR);
	ret.append(Util::formalize(startAddress, 6));
	ret.append(Util::SEPARATOR);
	ret.append(Util::formalize(Util::to_hexadecimal(_programLength), 6));
	return ret;
}

std::string Pass2::buildEnd(std::string startAddress) {
	return "E" + Util::SEPARATOR + Util::formalize(startAddress, 6);
}