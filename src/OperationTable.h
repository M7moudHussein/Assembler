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
#include <string>


class OperationTable {
public:
    static OperationTable *getInstance();

    bool hasOperation(std::string inst);

    int getFormat(std::string inst);

    int getOpCode(std::string inst);


private:
    static OperationTable *instance;
    std::unordered_map<std::string, OpInfo *> opTable;
    const char *INSTRUCTION_FILE = "instructions.txt";

    OperationTable();

    virtual ~OperationTable();

    void buildTable();
};

#endif /* OPERATIONTABLE_H_ */
