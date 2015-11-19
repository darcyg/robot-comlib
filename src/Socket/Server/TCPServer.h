/*
 * TCPServer.h
 *
 *  Created on: Jul 13, 2015
 *      Author: gabriel
 */

#ifndef SERVER_TCPSERVER_H_
#define SERVER_TCPSERVER_H_

#include <sys/types.h>

#include <vector>

#include "../TCPServerSocket.h"
#include "../../IO/FDListener.h"

class TCPServer : protected TCPServerSocket {
public:
	TCPServer();
	virtual ~TCPServer();

	void launch(uint port, uint backlog);
	void run();

	class Events {
	public:
		virtual void onClientConnected(TCPSocket* client) = 0;
		virtual void onClientDisconnected(TCPSocket* client) = 0;
		virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) = 0;
	};

	void setEvents(Events* events) {mevents = events;}
	void setFDListener(FDListener* listener) {mfdlistener = listener;}

private:
	using TCPServerSocket::bind;
	using TCPServerSocket::accept;
protected:
	std::vector<TCPSocket*> mclients;
	Events* mevents;
	FDListener* mfdlistener;
};

#endif /* SERVER_TCPSERVER_H_ */
