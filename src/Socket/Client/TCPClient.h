/*
 * TCPClient.h
 *
 *  Created on: Sep 8, 2015
 *      Author: gabriel
 */

#ifndef SOCKET_CLIENT_TCPCLIENT_H_
#define SOCKET_CLIENT_TCPCLIENT_H_

#include <thread>
#include <string>

#include "../TCPSocket.h"
#include "../../IO/FDListener.h"

class TCPClient : public TCPSocket, private FDListener {
public:
	TCPClient();
	virtual ~TCPClient();

	void launch(std::string address, int port);

	bool isConnected();

	class Events {
	public:
		virtual void onConnected(TCPClient* client) = 0;
		virtual void onConnectionFailed(TCPClient* client) = 0;
		virtual void onDisconnected(TCPClient* client) = 0;
		virtual void onMessageReceived(TCPClient* client, uint8_t buffer[], uint32_t len) = 0;
	};

	void setEvents(Events* events) {mevents = events;}

protected:
private:
	Events* mevents;
	bool mrunning;
	std::thread* mthread;

	void privaterun();
	using TCPSocket::connect;
};

#endif /* SOCKET_CLIENT_TCPCLIENT_H_ */
