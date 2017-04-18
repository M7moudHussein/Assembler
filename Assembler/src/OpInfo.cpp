/*
 * OpInfo.cpp
 *
 *  Created on: Apr 16, 2017
 *      Author: mahmoud
 */

#include "OpInfo.h"

OpInfo::OpInfo(int format, int code) : format(format), code(code) {
}

int OpInfo::getFormat() {
	return format;
}
int OpInfo::getCode() {
	return code;
}

OpInfo::~OpInfo() {

}

