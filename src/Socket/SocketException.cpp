/*
 * SocketException.cpp
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#include "SocketException.h"

SocketException::SocketException() : std::runtime_error("SocketException") {
	merrno = errno;
}


const char* SocketException::what() const throw ()  {
	return strcat("SocketException : ", strerror(merrno));
}
