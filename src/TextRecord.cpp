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

bool TextRecord::fits(std::string objectcode) {
    return size + objectcode.length() / 2 <= 30;
}

void TextRecord::append(std::string objectCode) {
    if (!textRecord.empty()) {
        size += objectCode.length() / 2;
    }
    textRecord.push_back(objectCode);
}

bool TextRecord::empty() {
    textRecord.empty();
}

std::string TextRecord::to_string() {
    std::string record = "T^";
    record.append(textRecord[0]);
    record.append("^");
    record.append(to_hexadecimal(size));
    for (int i = 1; i < (int) textRecord.size(); i++) {
        record.append("^");
        record.append(textRecord[i]);
    }
    record.append("\n");
    return record;
}

std::string TextRecord::to_hexadecimal(int number) {
    std::stringstream stream;
    stream << std::hex << number;
    return stream.str();
}
