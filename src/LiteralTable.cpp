#include "LiteralTable.h"

LiteralTable::LiteralTable() {

}

LiteralTable::~LiteralTable() {

}

void LiteralTable::addLiteral(std::string literal) {
	_newLits.push(literal);
}

void LiteralTable::addLiteral(std::string literal, int address) {
	_litTable.insert({literal, address});
}

int LiteralTable::arrangeTable(int locCtr) {
	while (!_newLits.empty()) {
		std::string curLit = _newLits.front();
		_newLits.pop();
		_litTable.insert({curLit, locCtr});
		if (tolower(curLit[1]) == 'w')
			locCtr += 3;
		else
			locCtr += Util::getConstSize(curLit);
	}
	return locCtr;
}

std::vector<std::pair<std::string, int> > LiteralTable::getData() {
	std::vector<std::pair<std::string, int> > vec;
	for (auto it : _litTable) {
		std::string lit = it.first;
		int adval = it.second;
		vec.push_back({lit, adval});
	}
	return vec;
};

int LiteralTable::getAddress(std::string literal) {
	return _litTable[literal];
}
