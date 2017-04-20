#include "SymbolTable.h"
#include <unordered_map>
#include <algorithm>
SymbolTable::SymbolTable() {

}

SymbolTable::~SymbolTable() {

}

bool SymbolTable::hasLabel(std::string label) {
    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    return table.count(label);
}

void SymbolTable::addLabel(std::string label, int address) {
    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    table[label] = address;
}

int SymbolTable::getAddress(std::string label){
    std::transform(label.begin(), label.end(), label.begin(), ::tolower);
    return table[label];
}

