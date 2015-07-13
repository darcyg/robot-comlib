/*
 * TCPServerSocket.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: gabriel
 */

#include "TCPServerSocket.h"

TCPServerSocket::TCPServerSocket() {
	/* Crée un point d'entrée-sortie représenté par un file descriptor permettant au process de communiquer avec l'extérieur.
	 * Paramètres :
	 * 	int domain : Famille de protocole de communication. AF_INET correspond à l'IPv4.
	 * 	int type : Mode de séquencement utilisé. SOCK_STREAM correspond à une communication en flux de données.
	 *	int protocol : Spécifie le protocole utilisé. TODO : Trouver pourquoi 0.
	 * Retour :
	 * 	int : File descriptor du point de sortie.
	 */
	msocket = ::socket(AF_INET, SOCK_STREAM, 0);

	if(msocket == -1) {
		perror("socket() : Cannot create an endpoint");
		exit(EXIT_FAILURE);
		//TODO : Throw exception
	}
}

TCPServerSocket::~TCPServerSocket() {
	close();
}

void TCPServerSocket::bind(uint port, uint backlog) {
	minfo.sin_addr.s_addr = htonl(INADDR_ANY); //N'importe quelle adresse
	minfo.sin_port = htons(port); //Port de communication
	minfo.sin_family = AF_INET; //IPv4

	if(::bind(msocket, (struct sockaddr*)&minfo, sizeof(minfo)) == -1) {
		perror("bind() : Cannot bind");
		exit(EXIT_FAILURE);
		//TODO : Throw exception
	}

	if(::listen(msocket, backlog) == -1) {
		perror("listen() : Cannot listen");
		exit(EXIT_FAILURE);
		//TODO : Throw exception
	}
}

TCPSocket& TCPServerSocket::accept() {
	//Préparation des éléments à récupérer
	struct sockaddr_in info = {0};
	socklen_t infosize = sizeof(info);

	//On accepte la connection entrante
	Socket clientsocket = ::accept(msocket, (struct sockaddr*)&info, &infosize);
	if(clientsocket == -1) {
		//TODO : Throw exception
	}

	return new TCPSocket(clientsocket, info);
}

void TCPServerSocket::close() {
	if(!isClosed()) {
		if(::close(msocket) != 0) {
			//TODO : Throw exception
		}
		msocket = 0;
	}
}

bool TCPServerSocket::isClosed() {
	return msocket == 0;
}
