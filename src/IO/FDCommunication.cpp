/*
 * FDCommunication.cpp
 *
 *  Created on: Jul 20, 2015
 *      Author: gabriel
 */

#include "FDCommunication.h"

FDCommunication::FDCommunication() {
	mfd = 0;
}

uint FDCommunication::read(void* buf, uint size) throw(IOException) {
	if(isClosed()) {
		throw IOException();
	}
	else {
		uint res;
		if((res = ::read(mfd, buf, size)) < 0) {
			throw IOException();
		}
		return res;
	}
}

uint FDCommunication::write(const void* buf, uint size) throw(IOException) {
	if(isClosed()) {
		throw IOException();
	}
	else {
		uint res;
		if((res = ::write(mfd, buf, size)) < 0) {
			throw IOException();
		}
		return res;
	}
}

void FDCommunication::close() throw(IOException) {
	if(!isClosed()) {
		if(::close(mfd) != 0) {
			throw IOException();
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
