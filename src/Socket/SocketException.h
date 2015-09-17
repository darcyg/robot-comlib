/*
 * SocketException.h
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#ifndef SOCKET_SOCKETEXCEPTION_H_
#define SOCKET_SOCKETEXCEPTION_H_

#include <errno.h>
#include <string.h>

#include <stdexcept>

class SocketException: public std::runtime_error {
public:
	SocketException();

	virtual const char* what() const throw();

private:
	int merrno;
};

#endif /* SOCKET_SOCKETEXCEPTION_H_ */
