#ifndef ASSEMBLER_LITERALTABLE_H
#define ASSEMBLER_LITERALTABLE_H

#include <string>
#include <queue>
#include <unordered_map>
#include "Util.hpp"

class LiteralTable {

public:
    LiteralTable();
    ~LiteralTable();

    void addLiteral(std::string);
    int arrangeTable(int locCtr);
    std::vector<std::pair<std::string, int> > getData();
    void addLiteral(std::string, int);
    int getAddress(std::string);

private:
    std::queue<std::string> _newLits;
    std::unordered_map<std::string, int> _litTable;
};


#endif //ASSEMBLER_LITERALTABLE_H
