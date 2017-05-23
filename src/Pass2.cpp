#include <algorithm>
#include "Pass2.hpp"

Pass2::Pass2(std::string interFile, int programLength) :
		_interFile(interFile), _programLength(programLength) {
}

void Pass2::generateObjFile(std::string output, std::string listFile) {
	compute(output, listFile);
}

void Pass2::compute(std::string output, std::string listFile) {
	std::ofstream outputStream(output);
	std::ofstream listStream(listFile);
	std::ifstream interStream(_interFile);
	TextRecord textRecord = TextRecord();
	std::string startAddress;
	std::string stringInput;
	std::string symbolData;
	std::getline(interStream, symbolData);
	initSymbolTable(symbolData);
	while (!interStream.eof()) {
		Line line;
		interStream >> line;
		if(line.isComment() || line.isEQU() || line.isORG() || line.isLTORG()){
			listStream << line << std::endl;
			continue;
		}
		if (line.isStart()) {
			outputStream << buildHeader(line, startAddress) << std::endl;
			listStream << line << std::endl;
		} else if (line.isEnd()) {
			listStream << line << std::endl;
			if (!textRecord.empty()) {
				outputStream << textRecord << std::endl;
			}
			outputStream << buildEnd(startAddress) << std::endl;
			break;
		} else {
			std::string objectCode = line.getObjectCode(*symbolTable);
			listStream << line << "\t\t" << objectCode << std::endl;
			if (objectCode.empty()) {
				if (!textRecord.empty()) {
					outputStream << textRecord << std::endl;
					textRecord = TextRecord();
				}
				continue;
			} else {
				if (textRecord.empty()) {
					textRecord.setStartingAddress(Util::formalize(Util::to_hexadecimal(line.getAddress()), 6));
				}
				if (textRecord.fits(objectCode)) {
					textRecord.append(objectCode);
				} else {
					outputStream << textRecord << std::endl;
					textRecord = TextRecord();
					textRecord.setStartingAddress(Util::formalize(Util::to_hexadecimal(line.getAddress()), 6));
					textRecord.append(objectCode);
				}
			}
		}
	}
	listStream.close();
	interStream.close();
	outputStream.close();
}

void Pass2::initSymbolTable(std::string data) {
	std::vector<std::string> vec = Util::split(data, ',');
	symbolTable = new SymbolTable();
	for(int i = 0; i < vec.size(); i += 2){
		symbolTable->addLabel(vec[i], std::stoi(vec[i + 1]));
	}
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
	std::string progLen = Util::formalize(Util::to_hexadecimal(_programLength), 6);
	std::transform(progLen.begin(), progLen.end(), progLen.begin(), ::toupper);
	ret.append(Util::formalize(progLen, 6));
	return ret;
}

std::string Pass2::buildEnd(std::string startAddress) {
	return "E" + Util::SEPARATOR + Util::formalize(startAddress, 6);
}