#ifndef ASSEMBLER_UTIL_HPP
#define ASSEMBLER_UTIL_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SymbolTable.h"

/**
 * Util is a different namespace used to encapsulate the functions
 * that are used as utilities belonging to no certain class and used
 * in different classes. As you can't define const static function
 * members in classes in c++ and that may affect their usage in const
 * member functions.
 */

namespace Util {

	const static char *DIRECTIVES[] = {"start", "end", "resw", "resb", "word", "byte", "equ", "org", "ltorg"};
	const static int DIR_SIZE = 9;

	/**
	 * Separator used to object code to enhance readability.
	 */
	const std::string SEPARATOR = "^";

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
	 * Checks if two characters are equal ignoring the capitalization
	 * @param First character
	 * @param second character
	 * @return returns true in case of equality
	 */
	bool equalsIgnoreCase(const char &, const char &);

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

	/**
	 * Checks for the existance of a certain character
	 * in a string.
	 * @return true if the character exists in this string.
	 */
	bool hasCharacter(std::string, char);

	/**
	 * Checks if a given string represents a directive or not.
	 * @return true in case if the given string represents the directive.
	 */
	bool isDirective(std::string);

	/**
	 * Checks if a given string represents a valid label.
	 * @return true in case the string can represent a label
	 */
	bool validLabel(std::string);

	/**
	 * Checks if a given string represents a valid operation.
	 * @return true in case the string represents an operation.
	 */
	bool validOperation(std::string);

	/**
	 * @return true in case if the string represents a valid operand
	 */
	bool validOperand(std::string);

	/**
	 * Checks if an operand is in an indexed mode.
	 * @return true if it can represents an indexed mode
	 */
	bool validIndexed(std::string);

	/**
	 * Checks if a string represents a valid Hexadecimal number
	 * @return true in case of valid hexa decimal number
	 */
	bool validHexa(std::string);

	/**
	 * Checks if a given character is a hexadecimal character
	 * or not.
	 */
	bool isHexaCharacter(char);


	/**
	 * Checks that an integer array given and separated by
	 * only spaces is valid and all the integers that are
	 * contained with in this array are valid.
	 */
	bool validHexaArray(std::string);

	/**
	 * The function takes a Mathematical expressions along
	 * with label as a values in this expression where it
	 * replaces the label using the symbol table.
	 * @return true in case it's a valid mathematical
	 * expression containing only + and -.
	 */
	bool validMathExpression(std::string, SymbolTable *);

	/**
	 * The function Evaluates the value of a mathematical
	 * expression and returns its value where this expression
	 * may contain only '+' and '-' without the appearance
	 * of any space character and it may contain symbols
	 * but that are only included in the symbolTable
	 * else it'll fail to find the right address.
	 */
	int evalMathExpression(std::string, SymbolTable *, int);

	/**
	 * The function checks the literal whether it's a
	 * valid literal or not and the validation check
	 * depends on the type of the literal whether it's
	 * a word or byte.
	 * @return true in case of a valid literal satisfying
	 * the above declared conditions.
	 */
	bool validLiteral(std::string);

	/**
	 * In case of checking a literal the byte and hexa
	 * can be verified using the validbyte and validhexa
	 * but the literal word needs to be changed to a
	 * normal integer and then is verified using the
	 * validInteger
	 * @return true in case it's a valid literal word.
	 */
	bool validLiteralWord(std::string);
};

#endif //ASSEMBLER_UTIL_HPP