#ifndef ASSEMBLER_UTIL_HPP
#define ASSEMBLER_UTIL_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * Util is a different namespace used to encapsulate the functions
 * that are used as utilities belonging to no certain class and used
 * in different classes. As you can't define const static function
 * members in classes in c++ and that may affect their usage in const
 * member functions.
 */

namespace Util {

    /**
     * Validates whether this string represents a valid integer or not
     * Doesn't handle floats or double.
     * @param integer a string to be validated
     * @return returns true in case of valid integer
     */
    bool validInteger(const std::string integer);

    /**
     * Validates whether this string represents a valid byte instance for
     * the sic machine, as an example C'Hello World!' or X'F54A'
     * @param charSeq a string to be validated
     * @return returns true in case of valid byte
     */
    bool validByte(const std::string charSeq);

    /**
     * Checks if two strings are equal ignoring the capitalization
     * of characters in the validation process.
     * @param str1 First string
     * @param str2 a const char array specified by the developer
     * @return returns true in case of equality
     */
    bool equalsIgnoreCase(const std::string &str1, const char *str2);

    /**
     * changes an integer from a base 10 to a base 16 number
     * represented using a string
     * @param number the integer to be changed
     * @return the base 16 string
     */
    std::string to_hexadecimal(int number);

    /**
     * changes an string which represents a number from a base
     * 10 to a base 16 number represented using a string
     * Throws an exception in case of non valid integer
     * @param number the integer to be changed
     * @return the base 16 string
     */
    std::string to_hexadecimal(const std::string number);

    /**
     * Formalizes a string representing code or number by
     * adding zero characters to its beginning to satisfy
     * certain length.
     * @param code
     * @param len
     * @return
     */
    std::string formalize(std::string code, const int len);

    /**
     * Splits a string into multiple strings using a prespecified
     * character as a separator for the strings.
     * @return a vector of strings which are separated.
     */
    std::vector<std::string> split(std::string, char);

    /**
     * Calculates the size of a byte array
     * such as C'Hello' is equal to 5
     * X'5f8a' is equal to 2
     * @return
     */
    int getConstSize(std::string);
};

#endif //ASSEMBLER_UTIL_HPP
