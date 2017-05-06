#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <string>
#include <unordered_map>
#include <vector>

/**
 * Symbol table class which uses an unordered map which is
 * a hashing based dictionary used to store symbols and
 * their addresses.
 */
class SymbolTable {
public:

	SymbolTable();
	virtual ~SymbolTable();

	/**
	 * Checks if this symbol table instance has the specified
	 * label.
	 * @return true in case of existence of this label in the unordered_map
	 */
	bool hasLabel(std::string);

	/**
	 * Adds a label and its specified address to the unordered_map.
	 */
	void addLabel(std::string, int);

	/**
	 *
	 * @return the address of the label specified by the string
	 * In case of not existing in the symbol table, It returns the
	 * default initialization value set in the c++ unordered_map, '0'.
	 */
	int getAddress(std::string);

	/**
	 * @return all the data associated with the table as vector of pairs
	 * where the first value of each pair is the symbol and the second
	 * value represents the address of this symbol.
	 */
	std::vector<std::pair<std::string, int> > getData();

private:
	std::unordered_map<std::string, int> table;
};

#endif /* SYMBOLTABLE_H_ */
