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
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include <stdlib.h>
#include "stdarg.h"
#include <termios.h>

#define UART_BUFFER_MAX_SIZE 128

class UARTSerial : public FDCommunication {
public:
	UARTSerial(char* device);
	virtual ~UARTSerial();

};

#endif /* UARTSERIAL_H_ */
