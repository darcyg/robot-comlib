/*
 * UARTSerial.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef UARTSERIAL_H_
#define UARTSERIAL_H_


#include "../IO/FDCommunication.h"
#include <stdint.h>

#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/stat.h"
#include <stdlib.h>
#include "stdarg.h"
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <string>

class UARTSerial : public FDCommunication {
public:
	UARTSerial();
	virtual ~UARTSerial();

	void open(const std::string& device) throw(IOException);

private:
	void init();

protected:

};

#endif /* UARTSERIAL_H_ */
