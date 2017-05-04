/*
 * SymbolTable.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <string>
#include <unordered_map>
#include <vector>

class SymbolTable {
public:
	SymbolTable();
	virtual ~SymbolTable();
	bool hasLabel(std::string);
	void addLabel(std::string, int);
	int getAddress(std::string);
	std::vector<std::pair<std::string, int> > getData();

private:
	std::unordered_map<std::string, int> table;
};

#endif /* SYMBOLTABLE_H_ */
