//
// Created by mahmoud on 4/19/17.
//

#include <sstream>
#include <algorithm>
#include "TextRecord.h"
#include "Util.hpp"


TextRecord::TextRecord() {
	size = 0;
}

TextRecord::~TextRecord() {
}

std::ostream &operator<<(std::ostream &os, const TextRecord &record) {
	std::string hexaSize = Util::formalize(Util::to_hexadecimal(record.size), 2);
	std::transform(hexaSize.begin(), hexaSize.end(), hexaSize.begin(), ::toupper);
	os << 'T' << Util::SEPARATOR << record.startingAddress << Util::SEPARATOR << hexaSize;
	for (unsigned int i = 0; i < record.textRecord.size(); i++) {
		os << Util::SEPARATOR << record.textRecord[i];
	}
	return os;
}

bool TextRecord::fits(std::string &objectCode) {
	std::vector<std::string> vec = Util::split(objectCode, '^');
	int newCodeSize = 0;
	for (unsigned int i = 0; i < vec.size(); i++) {
		newCodeSize += vec[i].length() / 2;
	}
	return size + newCodeSize <= 30;
}

void TextRecord::append(std::string objectCode) {
	size += objectCode.length() / 2;
	textRecord.push_back(objectCode);
}

bool TextRecord::empty() {
	textRecord.empty();
}

void TextRecord::setStartingAddress(std::string startingAddress) {
	std::transform(startingAddress.begin(), startingAddress.end(), startingAddress.begin(), ::toupper);
	this->startingAddress = startingAddress;
}
