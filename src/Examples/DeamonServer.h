/*
 * DeamonServer.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef DEAMONSERVER_H_
#define DEAMONSERVER_H_

#include <iostream>

#include "../Socket/Server/TCPServer.h"

class DeamonServer : public FDListener, TCPServer::Events {
public:
	DeamonServer();
	virtual ~DeamonServer();

	void launch();

	virtual void onClientConnected(TCPSocket* client) const;
	virtual void onClientDisconnected(TCPSocket* client) const;
	virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const;
private:
	TCPServer mtcpserver;
};

#endif /* DEAMONSERVER_H_ */
