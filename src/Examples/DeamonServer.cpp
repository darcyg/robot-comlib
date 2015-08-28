/*
 * DeamonServer.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "DeamonServer.h"

DeamonServer::DeamonServer() : FDListener() {
	mtcpserver.setFDListener(this);
	mtcpserver.setListener(this);
	mtcpserver.launch(3000, 10);
}

DeamonServer::~DeamonServer() {
}

void DeamonServer::launch() {
	for(;;) {
		listen();
		mtcpserver.run();
	}
}

void DeamonServer::onClientConnected(TCPSocket* client) const {
	std::cout << "New client connected" << std::endl;
}

void DeamonServer::onClientDisconnected(TCPSocket* client) const {
	std::cout << "A client has disconnected" << std::endl;
}

void DeamonServer::onMessageReceived(TCPSocket* client, uint8_t buffer[], uint8_t len) const {
	std::cout << "New message ! Length : " << (int)len << std::endl;
}
