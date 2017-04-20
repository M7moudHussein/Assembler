//
// Created by mahmoud on 4/19/17.
//

#ifndef ASSEMBLER_TEXTRECORD_H
#define ASSEMBLER_TEXTRECORD_H

#include <string>
#include <vector>

class TextRecord {
public:
    TextRecord();

    ~TextRecord();

    bool fits(std::string objectcode);

    void append(std::string objectCode);

    bool empty();

    std::string to_string();

private:
    std::vector<std::string> textRecord;
    int size;

    std::string to_hexadecimal(int size);
};


#endif //ASSEMBLER_TEXTRECORD_H
