//
// Created by mahmoud on 4/19/17.
//

#ifndef ASSEMBLER_TEXTRECORD_H
#define ASSEMBLER_TEXTRECORD_H

#include <string>
#include <vector>

class TextRecord {
public:
	TextRecord();

	~TextRecord();

	friend std::ostream &operator<<(std::ostream &, const TextRecord &);

	bool fits(std::string&);

	void append(std::string objectCode);

	bool empty();

	void setStartingAddress(std::string);

private:
	std::vector<std::string> textRecord;
	int size;
	std::string startingAddress;
};


#endif //ASSEMBLER_TEXTRECORD_H
