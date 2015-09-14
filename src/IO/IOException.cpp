/*
 * IOException.cpp
 *
 *  Created on: Sep 9, 2015
 *      Author: gabriel
 */

#include "IOException.h"

IOException::IOException() : std::runtime_error("IOException") {
	merrno = errno;
}

const char* IOException::what() const throw ()  {
	return strcat("IOException : ", strerror(merrno));
}
