/*
 * DeamonServer.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: gabriel
 */

#include "DeamonServer.h"

DeamonServer::DeamonServer() : TCPServerSocket(), FDListener() {
	mclients = std::vector<TCPSocket*>();
	mlistener = nullptr;
}

DeamonServer::~DeamonServer() {
	for (std::vector< TCPSocket* >::iterator it = mclients.begin() ; it != mclients.end(); ++it)
	{
		mclients.erase(it);
	}
	mclients.clear();
}

void DeamonServer::launch(uint port, uint backlog) {
	bind(port, backlog);

	addFD(this);

	for(;;) {

		// On écoute les FDs
		listen();

		///////////////////////////////////////////////////////////////////////
		///////////////////////    Partie Réception   /////////////////////////
		///////////////////////////////////////////////////////////////////////

		//Si le serveur reçoit une requête, alors il s'agit d'une nouvelle connection client.
		if(isFDReceiving(this)) {
			printf("New client connected.\n");

			TCPSocket* newclient = accept();

			if(mlistener) mlistener->onClientConnected(newclient);

			mclients.push_back(newclient);
			addFD(newclient);
		}

		//On vérifie si les clients ont envoyé des infos
		for (std::vector< TCPSocket* >::iterator it = mclients.begin() ; it != mclients.end(); ++it) {
			TCPSocket* client = *it;

			//Données reçues
			if(isFDReceiving(client)) {

				// Donne la taille de la donnée reçue
				uint count = client->getReadSize();

				// Déconnecté
				if(count == 0) {
					if(mlistener) mlistener->onClientDisconnected(*it);
					client->close();
					remFD(client);
					delete(client);
					it = mclients.erase(it);
				}
				//Nouveau message
				else {
					uint8_t* data = new uint8_t[count];

					client->read(data, count);

					if(mlistener) mlistener->onMessageReceived(client, data, count);
				}
			}
			else {
			}
		}


		///////////////////////////////////////////////////////////////////////
		///////////////////////   Partie Traitement   /////////////////////////
		///////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		////////////////////////    Partie Envoie    //////////////////////////
		///////////////////////////////////////////////////////////////////////

	}
}
