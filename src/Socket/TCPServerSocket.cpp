/*
 * TCPServerSocket.cpp
 *
 *  Created on: Jul 9, 2015
 *      Author: gabriel
 */

#include "TCPServerSocket.h"

TCPServerSocket::TCPServerSocket() throw(SocketException) {
	/* Crée un point d'entrée-sortie représenté par un file descriptor permettant au process de communiquer avec l'extérieur.
	 * Paramètres :
	 * 	int domain : Famille de protocole de communication. AF_INET correspond à l'IPv4.
	 * 	int type : Mode de séquencement utilisé. SOCK_STREAM correspond à une communication en flux de données.
	 *	int protocol : Spécifie le protocole utilisé. TODO : Trouver pourquoi 0.
	 * Retour :
	 * 	int : File descriptor du point de sortie.
	 */
	mfd = ::socket(AF_INET, SOCK_STREAM, 0);

	if(mfd == -1) {
		throw SocketException();
	}

	setsockopt(mfd, SOL_SOCKET, SO_REUSEADDR, NULL, NULL);
}

TCPServerSocket::~TCPServerSocket() {
	close();
}

void TCPServerSocket::bind(uint port, uint backlog) throw(SocketException) {
	minfo.sin_addr.s_addr = htonl(INADDR_ANY); //N'importe quelle adresse
	minfo.sin_port = htons(port); //Port de communication
	minfo.sin_family = AF_INET; //IPv4

	if(::bind(mfd, (struct sockaddr*)&minfo, sizeof(minfo)) == -1) {
		perror("bind() : Cannot bind");
		throw SocketException();
	}

	if(::listen(mfd, backlog) == -1) {
		throw SocketException();
	}
}

TCPSocket* TCPServerSocket::accept() throw(SocketException) {
	//Préparation des éléments à récupérer
	struct sockaddr_in info = {0};
	socklen_t infosize = sizeof(info);

	//On accepte la connection entrante
	FD clientsocket = ::accept(mfd, (struct sockaddr*)&info, &infosize);
	if(clientsocket == -1) {
		throw SocketException();
	}

	return new TCPSocket(clientsocket, info);
}
