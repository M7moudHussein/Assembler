#include "SymbolTable.h"
#include <unordered_map>

SymbolTable::SymbolTable() {

}

SymbolTable::~SymbolTable() {

}

bool SymbolTable::hasLabel(std::string label) {
    return table.count(label);
}

void SymbolTable::addLabel(std::string label, int address) {
    table[label] = address;
}

int SymbolTable::getAddress(std::string label){
    return table[label];
}

