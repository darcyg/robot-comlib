/*
 * UARTSerial.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "UARTSerial.h"

UARTSerial::UARTSerial() : FDCommunication() {
	init();
}


UARTSerial::~UARTSerial(){
	close();
}

void UARTSerial::open(const std::string& device) throw(IOException) {
	mfd = ::open(device.c_str(), O_RDWR | O_NOCTTY);
	if (mfd < 0) {
		throw IOException();
	}
	else {
		init();
	}
}

void UARTSerial::init(){
	struct termios   options;    // Terminal options
	int              rc;         // Return value
	// Get the current options for the port
	if((rc = tcgetattr(mfd, &options)) < 0){
		fprintf(stderr, "failed to get attr: %d, %s\n", mfd, strerror(errno));
	}

	cfsetispeed(&options, mbaudrate);
	cfsetospeed(&options, mbaudrate);

	cfmakeraw(&options);
	options.c_cflag |= (CLOCAL | CREAD);   // Enable the receiver and set local mode
	options.c_cflag &= ~CSTOPB;            // 1 stop bit
	options.c_cflag &= ~CRTSCTS;           // Disable hardware flow control
	options.c_cc[VMIN]  = 1;
	options.c_cc[VTIME] = 2;

	// Set the new attributes
	if((rc = tcsetattr(mfd, TCSANOW, &options)) < 0){
		fprintf(stderr, "failed to set attr: %d, %s\n", mfd, strerror(errno));
	}
}

