#ifndef LINE_H_
#define LINE_H_

#include <string>
#include <vector>

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

    bool hasAddress() const;

    bool hasLabel() const;

    bool hasOperand() const;

    bool hasComment() const;

    int setAddress(int);

    int getNextAddress(int);

    bool isValid();

    std::string getError();

    std::string getAddress() const;

    std::string getHexAddress() const;

    int getIntAddress() const;

    std::string getLabel() const;

    std::string getOperation() const;

    std::string getOperand() const;

    std::string getComment() const;

    bool isEnd() const;

private:
    std::string address, label, operation, operand, comment;

    void parseLine(std::string line);

    ReadState getNextState(ReadState);

    int getConstSize();

    void reformData();

    bool validInteger(std::string);
    bool validByte(std::string);
    std::vector<std::string> split(std::string, char) const;
    bool equalsIgnoreCase(const std::string &str1, const char *str2) const;
};

#endif /* LINE_H_ */
