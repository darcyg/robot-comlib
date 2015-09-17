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
		virtual void onConnected() const = 0;
		virtual void onConnectionFailed() const = 0;
		virtual void onDisconnected() const = 0;
		virtual void onMessageReceived(uint8_t buffer[], uint8_t len) const = 0;
	};

	void setEvents(Events* events) {mevents = events;}

protected:
private:
	Events* mevents;
	bool mrunning;
	std::thread* mthread;

	void privaterun();
};

#endif /* SOCKET_CLIENT_TCPCLIENT_H_ */
