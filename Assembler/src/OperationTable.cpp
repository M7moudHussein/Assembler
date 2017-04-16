/*
 * OperationTable.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "OperationTable.h"

OperationTable::OperationTable() {
	initialize();
}

static OperationTable OperationTable::getInstance() {
	return instance;
}

void OperationTable::initialize() {

}

OperationTable::~OperationTable() {
	// TODO Auto-generated destructor stub
}

