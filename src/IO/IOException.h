/*
 * IOException.h
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#ifndef IO_IOEXCEPTION_H_
#define IO_IOEXCEPTION_H_

#include <exception>

class IOException : std::exception {
	virtual const char* what() const throw() {
		return "IOException";
	}
};

#endif /* IO_IOEXCEPTION_H_ */
