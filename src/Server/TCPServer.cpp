/*
 * DeamonServer.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: gabriel
 */

#include "TCPServer.h"

TCPServer::TCPServer(FDListener* listener) : TCPServerSocket() {
	mclients = std::vector<TCPSocket*>();
	mfdlistener = listener;
	mevents = nullptr;
}

TCPServer::~TCPServer() {
	for (std::vector< TCPSocket* >::iterator it = mclients.begin() ; it != mclients.end(); ++it)
	{
		mclients.erase(it);
	}
	mclients.clear();
}

void TCPServer::launch(uint port, uint backlog) {
	bind(port, backlog);

	mfdlistener->addFD(this);
}

void TCPServer::run() {
	//Si le serveur reçoit une requête, alors il s'agit d'une nouvelle connection client.
	if(mfdlistener->isFDReceiving(this)) {
		TCPSocket* newclient = accept();

		if(mevents) mevents->onClientConnected(newclient);

		mclients.push_back(newclient);
		mfdlistener->addFD(newclient);
	}

	//On vérifie si les clients ont envoyé des infos
	for (std::vector< TCPSocket* >::iterator it = mclients.begin() ; it != mclients.end(); ++it) {
		TCPSocket* client = *it;

		//Données reçues
		if(mfdlistener->isFDReceiving(client)) {

			// Donne la taille de la donnée reçue
			uint count = client->getReadSize();

			// Déconnecté
			if(count == 0) {
				if(mevents) mevents->onClientDisconnected(*it);
				client->close();
				mfdlistener->remFD(client);
				delete(client);
				it = mclients.erase(it);
			}
			//Nouveau message
			else {
				uint8_t* data = new uint8_t[count];

				client->read(data, count);

				if(mevents) mevents->onMessageReceived(client, data, count);
			}
		}
		else {
		}
	}
}
