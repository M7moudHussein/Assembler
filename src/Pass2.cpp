#include <algorithm>
#include "Pass2.hpp"

Pass2::Pass2(SymbolTable *symbolTable, std::string interFile, int programLength) :
		symbolTable(symbolTable), _interFile(interFile), _programLength(programLength) {
}

void Pass2::generateObjFile(std::string output, std::string listFile) {
	compute(output, listFile);
}

void Pass2::compute(std::string output, std::string listFile) {
	std::ofstream outputStream(output);
	std::ofstream listStream(listFile);
	std::ifstream interStream(_interFile);
	TextRecord textRecord;
	std::string startAddress;
	std::string stringInput;
	while (!interStream.eof()) {
		Line line;
		interStream >> line;
		listStream << line;
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
			listStream << "\t" << line.getObjectCode(*symbolTable);
			std::string objectCode = line.getObjectCode(*symbolTable);
			if (!textRecord.fits(objectCode)) {
				outputStream << textRecord << std::endl;
				textRecord = TextRecord(Util::formalize(Util::to_hexadecimal(line.getAddress()), 6));
			}
			textRecord.append(objectCode);
		}
		listStream << std::endl;
	}
	listStream.close();
	interStream.close();
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
	std::string progLen = Util::to_hexadecimal(_programLength);
	std::transform(progLen.begin(), progLen.end(), progLen.begin(), ::toupper);
	ret.append(Util::formalize(progLen, 6));
	return ret;
}

std::string Pass2::buildEnd(std::string startAddress) {
	return "E" + Util::SEPARATOR + Util::formalize(startAddress, 6);
}