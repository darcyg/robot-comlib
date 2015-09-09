/*
 * SocketException.h
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#ifndef SOCKET_SOCKETEXCEPTION_H_
#define SOCKET_SOCKETEXCEPTION_H_

#include <exception>

class SocketException: public std::exception {
	virtual const char* what() const throw() {
		return "SocketException";
	}
};

#endif /* SOCKET_SOCKETEXCEPTION_H_ */
