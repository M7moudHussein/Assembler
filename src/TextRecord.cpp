//
// Created by mahmoud on 4/19/17.
//

#include <sstream>
#include <algorithm>
#include "TextRecord.h"
#include "Util.hpp"

TextRecord::TextRecord(std::string address) {
	startingAddress = address;
	size = 0;
}

TextRecord::~TextRecord() {

}

std::ostream &operator<<(std::ostream &os, const TextRecord &record) {
	std::string hexaSize = Util::to_hexadecimal(record.size);
	std::transform(hexaSize.begin(), hexaSize.end(), hexaSize.begin(), ::toupper);
	os << 'T' << Util::SEPARATOR << record.startingAddress << Util::SEPARATOR << hexaSize;
	for (int i = 0; i < (int) record.textRecord.size(); i++) {
		if (record.textRecord[i].empty()) {
			continue;
		}
		os << Util::SEPARATOR << record.textRecord[i];
	}
	return os;
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

TextRecord::TextRecord() {

}
