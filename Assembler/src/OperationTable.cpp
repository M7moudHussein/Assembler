/*
 * OperationTable.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "OperationTable.h"
OperationTable *instance;

OperationTable::OperationTable() {
	initialize();
}

OperationTable *OperationTable::getInstance() {
	if (instance == NULL) {
		instance = new OperationTable();
	}
	return instance;
}

void OperationTable::initialize() {
	// TODO Auto-generated destructor stub
}

OperationTable::~OperationTable() {
	// TODO Auto-generated destructor stub
}

