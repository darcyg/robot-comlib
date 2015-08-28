/*
 * FDCommunication.h
 *
 *  Created on: Jul 20, 2015
 *      Author: gabriel
 */

#ifndef FDCOMMUNICATION_H_
#define FDCOMMUNICATION_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>

typedef int FD;

class FDCommunication {
public :
	uint read(void* buf, uint size);
	uint write(const void* buf, uint size);

	uint getReadSize();

	FD getFD() {return mfd;}

	void close();
	bool isClosed();
protected :
	FD mfd;
};

#endif /* FDCOMMUNICATION_H_ */
