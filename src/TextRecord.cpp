//
// Created by mahmoud on 4/19/17.
//

#include <sstream>
#include "TextRecord.h"

TextRecord::TextRecord() {
    size = 0;
}

TextRecord::~TextRecord() {

}

std::ostream &operator<<(std::ostream &os, const TextRecord &record) {
    os << "T^" << "00" << record.startingAddress << "^" << record.to_hexadecimal(record.size);
    for (int i = 0; i < (int) record.textRecord.size(); i++) {
        os << "^" << record.textRecord[i];
    }
    return os;
}

bool TextRecord::fits(std::string objectcode) {
    return size + objectcode.length() / 2 <= 30;
}

void TextRecord::append(std::string objectCode, std::string instructionAddress) {
    if (startingAddress.empty()) {
        startingAddress = instructionAddress;
    }
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
