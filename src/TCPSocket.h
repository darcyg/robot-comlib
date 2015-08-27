/*
 * TCPSocket.h
 *
 *  Created on: Jun 27, 2015
 *      Author: gabriel
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

// Include Langage C //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Include Langage C++ //

#include <string>

#include "Message.h"
#include "FDCommunication.h"

class TCPSocket : public FDCommunication {
public:
	TCPSocket();
	TCPSocket(const std::string &ip, uint port);
	TCPSocket(FD socket,struct sockaddr_in info);

	virtual ~TCPSocket();
	void connect(const std::string &ip, uint port);

	bool isReceiving(uint timeoutms = 0);


protected:

	struct sockaddr_in minfo;
};

#endif /* TCPSOCKET_H_ */
