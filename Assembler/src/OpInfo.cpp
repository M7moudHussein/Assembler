/*
 * OpInfo.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "OpInfo.h"

OpInfo::OpInfo(short format, short code) :
		format(format), code(code) {
}

short OpInfo::getFormat() {
	return format;
}
short OpInfo::getCode() {
	return code;
}

OpInfo::~OpInfo() {
	// TODO Auto-generated destructor stub
}

