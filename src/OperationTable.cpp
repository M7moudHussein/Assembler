#include "OperationTable.h"
#include <fstream>
#include <algorithm>
#include <assert.h>

OperationTable *OperationTable::instance = NULL;

OperationTable::OperationTable() {
    buildTable();
}

OperationTable *OperationTable::getInstance() {
    if (instance == NULL) {
        instance = new OperationTable();
    }
    return instance;
}

OperationTable::~OperationTable() {
}

void OperationTable::buildTable() {
    std::ifstream is(INSTRUCTION_FILE);
    std::string inst;
    int format, opCode;
    while (is >> inst) {
        is >> opCode >> format;
        std::transform(inst.begin(), inst.end(), inst.begin(), ::tolower);
        opTable[inst] = new OpInfo(format, opCode);
    }
    assert(is.eof());
    is.close();
}

int OperationTable::getFormat(std::string inst) {
    std::transform(inst.begin(), inst.end(), inst.begin(), ::tolower);
    assert(opTable.count(inst));
    return opTable[inst]->getFormat();
}

int OperationTable::getOpCode(std::string inst) {
    std::transform(inst.begin(), inst.end(), inst.begin(), ::tolower);
    assert(opTable.count(inst));
    return opTable[inst]->getCode();
}

bool OperationTable::hasOperation(std::string inst) {
    std::transform(inst.begin(), inst.end(), inst.begin(), ::tolower);
    return opTable.count(inst);
}