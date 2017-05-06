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

	TextRecord(std::string);

	~TextRecord();

	friend std::ostream &operator<<(std::ostream &, const TextRecord &);

	bool fits(std::string objectcode);

	void append(std::string objectCode);

	bool empty();

	void setStartingAddress(std::string address);

private:
	std::vector<std::string> textRecord;
	int size;
	std::string startingAddress;

	std::string to_hexadecimal(int size) const;
};


#endif //ASSEMBLER_TEXTRECORD_H
