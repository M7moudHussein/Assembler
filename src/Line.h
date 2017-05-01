#ifndef LINE_H_
#define LINE_H_

#include <string>
#include <vector>
#include "OperationTable.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include "Util.hpp"

enum class ReadState {
    LABEL, OPERATION, OPERAND, COMMENT, INVALID
};

class Line {
public:
    Line();
    Line(std::string line);

    virtual ~Line();

    friend std::ostream &operator<<(std::ostream &, const Line &);
    friend std::istream& operator >> (std::istream& is, Line& c);

    int getNextAddress();

    bool fail();
    std::string getError();

    std::string getLabel() const;
    std::string getOperation() const;
    std::string getOperand() const;
    std::string getComment() const;

    int getIntAddress() const;
    std::string getAddress() const;
    std::string getHexAddress() const;


    bool isEnd() const;

private:
    std::string address, label, operation, operand, comment;
    std::string nextAddress, errorMessage;

    bool hasError, isComment;

    void parseLine(std::string line);
    ReadState getNextState(ReadState);
    void reformData();
};

#endif /* LINE_H_ */
