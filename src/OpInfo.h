/*
 * OpInfo.h
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#ifndef OPINFO_H_
#define OPINFO_H_

/**
 * Class used to store the data of the Operation
 * the format and the code value of it.
 */
class OpInfo {
public:
	OpInfo(int format, int code);
	virtual ~OpInfo();
	/**
	 * @return the format of this operation.
	 */
	int getFormat();
	/**
	 * @return the integer value of the operation.
	 */
	int getCode();
private:
	int format;
	int code;
};

#endif /* OPINFO_H_ */
