/*
 * OperationTable.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef OPERATIONTABLE_H_
#define OPERATIONTABLE_H_

class OperationTable {
public:
	static OperationTable getInstance();
private:
	static OperationTable instance;
	OperationTable();
	void initialize();
	virtual ~OperationTable();
};

#endif /* OPERATIONTABLE_H_ */
