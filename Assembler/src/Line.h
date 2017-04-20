#ifndef LINE_H_
#define LINE_H_

#include <string>

enum class ReadState {
    LABEL, OPERATION, OPERAND, COMMENT, INVALID
};

class Line {
public:
    Line(std::string line);

    virtual ~Line();

    friend std::ostream &operator<<(std::ostream &, const Line &);


    bool hasLabel();

    bool hasOperation();

    bool hasOperand();

    bool hasComment();

    void setAddress(int);

    int getNextAddress(int);

    bool isValid();

    std::string getError();

    std::string getLabel();

    std::string getOperation();

    std::string getOperand();

    std::string getComment();

private:
    std::string label, operation, operand, comment;
    bool readLabel, readOperation, readOperand, readComment;
    int address;

    void parseLine(std::string line);

    ReadState getNextState(ReadState);

    int getConstSize();

    void reformData();

    void reformLabel();
    bool validInteger(std::string);
    bool validByte(std::string);

    bool equalsIgnoreCase(std::string &str1, const char *str2);
};

#endif /* LINE_H_ */
