#ifndef ASSEMBLER_UTIL_HPP
#define ASSEMBLER_UTIL_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

namespace Util {
    bool validInteger(const std::string integer);
    bool validByte(const std::string charSeq);
    bool equalsIgnoreCase(const std::string &str1, const char *str2);
    std::string to_hexadecimal(int number);
    std::string to_hexadecimal(const std::string number);
    std::string formalize(std::string code, const int len);
    std::vector<std::string> split(std::string, char);
    int getConstSize(std::string);
};

#endif //ASSEMBLER_UTIL_HPP
