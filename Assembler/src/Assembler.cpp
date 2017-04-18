#include <iostream>
#include "OperationTable.h"

int main(int argc, char** argv){
    OperationTable* op = OperationTable::getInstance();
    std::cout << op->getOpCode("add") << "  EEEE" << std::endl;
    return 0;
}