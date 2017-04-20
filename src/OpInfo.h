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
	OpInfo(int format, int code);
	virtual ~OpInfo();
	int getFormat();
	int getCode();
private:
	int format;
	int code;
};

#endif /* OPINFO_H_ */
