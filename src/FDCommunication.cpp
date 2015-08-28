/*
 * FDCommunication.cpp
 *
 *  Created on: Jul 20, 2015
 *      Author: gabriel
 */

#include "FDCommunication.h"

uint FDCommunication::read(void* buf, uint size) {
	if(isClosed()) {
		return 0;
		//TODO : Throw exception
	}
	else {
		uint res;
		if((res = ::read(mfd, buf, size)) < 0) {
			//TODO : Throw exception
		}
		return res;
	}
}

uint FDCommunication::write(const void* buf, uint size) {
	if(isClosed()) {
		return 0;
		//TODO : Throw exception
	}
	else {
		uint res;
		if((res = ::write(mfd, buf, size)) < 0) {
			//TODO : Throw exception
		}
		return res;
	}
}

void FDCommunication::close() {
	if(!isClosed()) {
		if(::close(mfd) != 0) {
			//TODO : Throw exception
		}
		mfd = 0;
	}
}

uint FDCommunication::getReadSize() {
	uint count;
	::ioctl(mfd, FIONREAD, &count);
	return count;
}

bool FDCommunication::isClosed() {
	return mfd == 0;
}
