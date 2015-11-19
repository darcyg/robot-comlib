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
	mfd = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (mfd < 0) {
		throw IOException();
	}
}

void UARTSerial::init(){
	//utilisation buffer génériques
	struct termios tty_attributes;

	tcgetattr(mfd, &tty_attributes);
	// Enable receiver
	cfmakeraw(&tty_attributes);// indispensable pour desactiver caractères de controle!!! ex 0x11
	tty_attributes.c_cflag |= CREAD;

	// 8 data bit
	tty_attributes.c_cflag |= CS8;

	// c_iflag
	// Ignore framing errors and parity errors.
	tty_attributes.c_iflag |= IGNPAR;

	// c_lflag
	// DISABLE canonical mode.
	// Disables the special characters EOF, EOL, EOL2,
	// ERASE, KILL, LNEXT, REPRINT, STATUS, and WERASE, and buffers by lines.
	tty_attributes.c_lflag &= ~(ICANON);

	// DISABLE this: Echo input characters.
	tty_attributes.c_lflag &= ~(ECHO);

	// DISABLE this: If ICANON is also set, the ERASE character erases the preceding input
	// character, and WERASE erases the preceding word.
	tty_attributes.c_lflag &= ~(ECHOE);

	// DISABLE this: When any of the characters INTR, QUIT, SUSP, or DSUSP are received, generate the corresponding signal.
	tty_attributes.c_lflag &= ~(ISIG);

	/* polling read : Si data dispo read()
	 * retourne nb de bytes dispo ou nb bytes demandes.
	 */
	// Minimum number of characters for non-canonical read.
	tty_attributes.c_cc[VMIN] = 0;

	// Timeout in deciseconds for non-canonical read.
	tty_attributes.c_cc[VTIME] = 0;

	// Set the baud rate
	cfsetospeed(&tty_attributes, B9600);
	cfsetispeed(&tty_attributes, B9600);
	tcsetattr(mfd, TCSANOW, &tty_attributes);
	sleep(1);
}

