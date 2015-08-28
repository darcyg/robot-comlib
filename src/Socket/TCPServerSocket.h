/*
 * TCPServerSocket.h
 *
 *  Created on: Jul 9, 2015
 *      Author: gabriel
 */

#ifndef TCPSERVERSOCKET_H_
#define TCPSERVERSOCKET_H_

#include "TCPSocket.h"

class TCPServerSocket : public FDCommunication {
public:
	TCPServerSocket();

	virtual ~TCPServerSocket();

	void bind(uint port, uint backlog);
	TCPSocket* accept();

protected:
	struct sockaddr_in minfo;
};

#endif /* TCPSERVERSOCKET_H_ */
