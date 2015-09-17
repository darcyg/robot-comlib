/*
 * IOException.h
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#ifndef IO_IOEXCEPTION_H_
#define IO_IOEXCEPTION_H_

#include <errno.h>
#include <string.h>

#include <stdexcept>

class IOException : std::runtime_error {
public :
	IOException();
	virtual const char* what() const throw();

private:
	int merrno;
};

#endif /* IO_IOEXCEPTION_H_ */
