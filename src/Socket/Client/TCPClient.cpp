/*
 * TCPClient.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: gabriel
 */

#include "TCPClient.h"

TCPClient::TCPClient() {
	mrunning = false;
	mthread = nullptr;
	mevents = nullptr;
	addFD(this);
}

TCPClient::~TCPClient() {
	if(mrunning) {
		close();
		mthread->join();
	}
	delete(mthread);
}

void TCPClient::launch(std::string address, int port) {

	try {
		connect(address, port);
		if(mevents) mevents->onConnected(this);
			mrunning = true;
			mthread = new std::thread(&TCPClient::privaterun, this);
	}
	catch(SocketException &e) {
		if(mevents) mevents->onConnectionFailed(this);
	}
}

bool TCPClient::isConnected() {
	return mrunning;
}

void TCPClient::privaterun() {
	while(mrunning) {

		listen();

		// Donne la taille de la donnée reçue
		uint count = getReadSize();

		// Déconnecté
		if(count == 0) {
			if(mevents) mevents->onDisconnected(this);
			close();
			remFD(this);
			mrunning = false;
		}
		//Nouveau message
		else {
			uint8_t* data = new uint8_t[count];

			read(data, count);

			if(mevents) mevents->onMessageReceived(this, data, count);
			delete(data);
		}
	}
}
