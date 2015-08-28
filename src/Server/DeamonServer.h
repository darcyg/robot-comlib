/*
 * DeamonServer.h
 *
 *  Created on: Jul 13, 2015
 *      Author: gabriel
 */

#ifndef SERVER_DEAMONSERVER_H_
#define SERVER_DEAMONSERVER_H_

#include <sys/types.h>

#include <vector>
#include <thread>

#include "../TCPServerSocket.h"

class DeamonServer : protected TCPServerSocket, public FDListener {
public:
	DeamonServer();
	virtual ~DeamonServer();

	void launch(uint port, uint backlog);

	class Listener {
	public:
		virtual void onClientConnected(TCPSocket* client) const = 0;
		virtual void onClientDisconnected(TCPSocket* client) const = 0;
		virtual void onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const = 0;
	};

	void setListener(Listener* listener) {mlistener = listener;}

private:
protected:
	std::vector<TCPSocket*> mclients;
	Listener* mlistener;
};

#endif /* SERVER_DEAMONSERVER_H_ */
