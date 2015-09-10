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

#define UART_BUFFER_MAX_SIZE 128

class UARTSerial : public FDCommunication {
public:
	UARTSerial();
};

#endif /* UARTSERIAL_H_ */
