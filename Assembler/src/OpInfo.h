/*
 * OpInfo.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef OPINFO_H_
#define OPINFO_H_

class OpInfo {
public:
	OpInfo(short format, short code);
	virtual ~OpInfo();
	short getFormat();
	short getCode();
private:
	short format;
	short code;
};

#endif /* OPINFO_H_ */
