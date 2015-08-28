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
#include <thread>

#include "../TCPServerSocket.h"
#include "../FDListener.h"

class TCPServer : protected TCPServerSocket {
public:
	TCPServer(FDListener* listener);
	virtual ~TCPServer();

	void launch(uint port, uint backlog);

	void run();

	class Events {
	public:
		virtual void onClientConnected(TCPSocket* client) const = 0;
		virtual void onClientDisconnected(TCPSocket* client) const = 0;
		virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const = 0;
	};

	void setListener(Events* events) {mevents = events;}

private:
protected:
	std::vector<TCPSocket*> mclients;
	Events* mevents;
	FDListener* mfdlistener;
};

#endif /* SERVER_TCPSERVER_H_ */
