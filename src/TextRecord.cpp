//
// Created by mahmoud on 4/19/17.
//

#include <sstream>
#include "TextRecord.h"
#include "Util.hpp"

TextRecord::TextRecord(std::string address) {
	startingAddress = address;
	size = 0;
}

TextRecord::~TextRecord() {

}

std::ostream &operator<<(std::ostream &os, const TextRecord &record) {
	os << 'T' << Util::SEPARATOR << record.startingAddress << Util::SEPARATOR << record.to_hexadecimal(record.size);
	for (int i = 0; i < (int) record.textRecord.size(); i++) {
		if (record.textRecord[i].empty()) {
			continue;
		}
		os << Util::SEPARATOR << record.textRecord[i];
	}
	return os;
}

void TextRecord::setStartingAddress(std::string address) {
	startingAddress = address;
}

bool TextRecord::fits(std::string objectcode) {
	return size + objectcode.length() / 2 <= 30;
}

void TextRecord::append(std::string objectCode) {
	size += objectCode.length() / 2;
	textRecord.push_back(objectCode);
}

bool TextRecord::empty() {
	textRecord.empty();
}

std::string TextRecord::to_hexadecimal(int number) const {
	std::stringstream stream;
	stream << std::hex << number;
	return stream.str();
}

TextRecord::TextRecord() {

}
