/*
 * OperationTable.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef OPERATIONTABLE_H_
#define OPERATIONTABLE_H_

#include "OpInfo.h"
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

class OperationTable {
public:
	static OperationTable *getInstance();
private:
	std::unordered_map<std::string, OpInfo> opTable;
	OperationTable();
	void initialize();
	virtual ~OperationTable();
};

#endif /* OPERATIONTABLE_H_ */
