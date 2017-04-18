#ifndef LINE_H_
#define LINE_H_

#include <string>

enum class ReadState { LABEL, OPERATION, OPERAND, COMMENT, INVALID};

class Line {
public:
	Line(std::string line);
	virtual ~Line();

	bool hasLabel();
	bool hasOperation();
	bool hasOperand();
	bool hasComment();
	std::string getLabel();
	std::string getOperation();
	std::string getOperand();
	std::string getComment();
	ReadState getNextState(ReadState);

private:
	std::string label, operation, operand, comment;
	bool readLabel, readOperation, readOperand, readComment;

	void parseLine(std::string line);
};

#endif /* LINE_H_ */
