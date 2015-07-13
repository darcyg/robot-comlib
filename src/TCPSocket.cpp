/*
 * TCPSocket.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: gabriel
 */

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
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

TCPSocket::~TCPSocket() {
	close();
}

TCPSocket::TCPSocket(const std::string &ip, uint port) : TCPSocket() {
	connect(ip, port);
}

TCPSocket::TCPSocket(Socket socket, struct sockaddr_in info) {
	msocket = socket;
	minfo = info;
}

void TCPSocket::connect(const std::string &ip, uint port) {
	if(isClosed()) {
		//TODO : Throw exception
	}
	else {

		//Transforme l'adresse IP en chaine de caractère en long
		minfo.sin_addr.s_addr = inet_addr(ip.c_str());
		minfo.sin_port = htons(port); //Port de communication
		minfo.sin_family = AF_INET; //IPv4

		/* On essaie de ce connecter au serveur. Si celui-ci appelle la fonction accept()
		 * la connection s'effectuera.
		 */
		if(::connect(msocket, (struct sockaddr*)&minfo, sizeof(minfo)) == -1) {
			perror("connect() : Cannot connect to server");
			exit(EXIT_FAILURE);
			//TODO : Throw exception
		}
	}
}

void TCPSocket::close() {
	if(!isClosed()) {
		if(::close(msocket) != 0) {
			//TODO : Throw exception
		}
		msocket = 0;
	}
}

Socket TCPSocket::getSocket() {
	return msocket;
}

bool TCPSocket::isReceiving(uint timeoutms) {
	fd_set fdwatched;
	FD_ZERO(&fdwatched);
	FD_SET(msocket, &fdwatched);

	struct timeval timeout;
	timeout.tv_usec = (1000 * timeoutms%1000);
	timeout.tv_sec = (timeoutms/1000);

	return ::select(msocket + 1, &fdwatched, NULL, NULL, &timeout) == 1;
}

uint TCPSocket::read(void* buf, uint size) {
	if(isClosed()) {
		return 0;
		//TODO : Throw exception
	}
	else {
		uint res;
		if((res = ::read(msocket, buf, size)) < 0) {
			//TODO : Throw exception
		}
		return res;
	}
}

uint TCPSocket::write(const void* buf, uint size) {
	if(isClosed()) {
		return 0;
		//TODO : Throw exception
	}
	else {
		uint res;
		if((res = ::write(msocket, buf, size)) < 0) {
			//TODO : Throw exception
		}
		return res;
	}
}

bool TCPSocket::isClosed() {
	return msocket == 0;
}
