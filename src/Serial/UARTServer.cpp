/*
 * UARTServer.cpp
 *
 *  Created on: 12 sept. 2015
 *      Author: ethel
 */

#include "UARTServer.h"

UARTServer::UARTServer() : UARTSerial() {
	mevents = nullptr;
	mfdlistener = nullptr;
}

UARTServer::~UARTServer() {
}

void UARTServer::run() {
	if(mfdlistener->isFDReceiving(this)) {
		// Donne la taille de la donnée reçue
		uint count = getReadSize();

		// Déconnecté
		if(count == 0) {
			if(mevents) mevents->onDisconnected(this);
			close();
			mfdlistener->remFD(this);
		}
		//Nouveau message
		else {
			uint8_t* data = new uint8_t[count];

			read(data, count);

			if(mevents) mevents->onMessageReceived(this, data, count);
		}
	}
}

void UARTServer::launch(const std::string& device) {
	try {
		open(device);
		if(mevents) mevents->onConnected(this);
	}
	catch(IOException& e) {
		if(mevents) mevents->onConnectionFailed(this);
	}
	mfdlistener->addFD(this);
}

bool UARTServer::isConnected() {
	return !isClosed();
}
