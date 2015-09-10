/*
 * UARTSerial.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "UARTSerial.h"

UARTSerial::UARTSerial(char* device) : FDCommunication() {
	// TODO Auto-generated constructor stub

	mfd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (mfd < 0) {
		fprintf(stderr, "Open error on %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}


UARTSerial::~UARTSerial(){
	close();
}

