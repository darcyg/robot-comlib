/*
 * TCPSocket.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: gabriel
 */

#include "TCPSocket.h"

TCPSocket::TCPSocket() throw(SocketException) {
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
}

TCPSocket::~TCPSocket() {
	close();
}

TCPSocket::TCPSocket(const std::string &ip, uint port) : TCPSocket() {
	connect(ip, port);
}

TCPSocket::TCPSocket(FD socket, struct sockaddr_in info) {
	mfd = socket;
	minfo = info;
}

void TCPSocket::connect(const std::string &ip, uint port) throw(SocketException) {
	if(isClosed()) {
		throw SocketException();
	}
	else {

		//Transforme l'adresse IP en chaine de caractère en long
		minfo.sin_addr.s_addr = inet_addr(ip.c_str());
		minfo.sin_port = htons(port); //Port de communication
		minfo.sin_family = AF_INET; //IPv4

		/* On essaie de ce connecter au serveur. Si celui-ci appelle la fonction accept()
		 * la connection s'effectuera.
		 */
		if(::connect(mfd, (struct sockaddr*)&minfo, sizeof(minfo)) == -1) {
			throw SocketException();
		}
	}
}

bool TCPSocket::isReceiving(uint timeoutms) {
	fd_set fdwatched;
	FD_ZERO(&fdwatched);
	FD_SET(mfd, &fdwatched);

	struct timeval timeout;
	timeout.tv_usec = (1000 * timeoutms%1000);
	timeout.tv_sec = (timeoutms/1000);

	return ::select(mfd + 1, &fdwatched, NULL, NULL, &timeout) == 1;
}
