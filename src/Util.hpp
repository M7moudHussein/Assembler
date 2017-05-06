#ifndef ASSEMBLER_UTIL_HPP
#define ASSEMBLER_UTIL_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

namespace Util {
    const std::string SEPARATOR = "^";

    bool validInteger(const std::string);

    bool validByte(const std::string);

    bool equalsIgnoreCase(const std::string &, const char *);

    std::string to_hexadecimal(int);

    std::string to_hexadecimal(const std::string);

    int to_int(std::string hexadecimal_string);

    std::string formalize(std::string, const int);

    std::vector<std::string> split(std::string, char);

    int getConstSize(std::string);
};

#endif //ASSEMBLER_UTIL_HPP
