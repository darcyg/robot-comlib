/*
 * TCPServerSocket.h
 *
 *  Created on: Jul 9, 2015
 *      Author: gabriel
 */

#ifndef TCPSERVERSOCKET_H_
#define TCPSERVERSOCKET_H_

#include "TCPSocket.h"

class TCPServerSocket {
public:
	TCPServerSocket();

	virtual ~TCPServerSocket();

	void bind(uint port, uint backlog);
	TCPSocket& accept();

	void close();

	bool isClosed();

protected:
	Socket msocket;

	struct sockaddr_in minfo;
};

#endif /* TCPSERVERSOCKET_H_ */
