/*
 * FDListener.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "FDListener.h"


FDListener::FDListener() : mblock(false) {
	mtimeout = nullptr;
	mfdmax = 0;
	mfdwatched = std::vector<FDCommunication*>();
	FD_ZERO(&mfdset);
}

void FDListener::addFD(FDCommunication* newFD) {
	mfdmax = mfdmax > newFD->getFD() ? mfdmax : newFD->getFD();
	mfdwatched.push_back(newFD);
}

void FDListener::remFD(FDCommunication* FD) {
	for (std::vector< FDCommunication* >::iterator it = mfdwatched.begin() ; it != mfdwatched.end(); ++it) {
		if(*it == FD) {
			mfdwatched.erase(it);
			break;
		}
	}
}

void FDListener::listen() throw(IOException) {
	//On remet à zéro
	FD_ZERO(&mfdset);

	//On charge les FDs (Files Descriptors) à surveiller.
	for (std::vector< FDCommunication* >::iterator it = mfdwatched.begin() ; it != mfdwatched.end(); ++it) {
		FD_SET((*it)->getFD(), &mfdset);
	}

	int res;

	/* int select (int nfds, fd_set *read-fds, fd_set *write-fds, fd_set *except-fds, struct timeval *timeout)
	 *
	 * Gros conseil pour mieux comprendre : "man select" dans la console linux.
	 * Select permet de détecter quand des FDs sont prêts à être lus.
	 * Intérêt : On évite d'utilisé une fct bloquante comme send et recv alors qu'il n'y en a pas besoin.
	 *
	 * Il faut lui envoyer en premier paramètre (nfds) le FD avec le plus grand numéro plus un.
	 * Pas d'explication à ça, le manuel n'en dit pas plus.
	 * read-fds : FDs qu'on veut surveiller en lecture.
	 * write-fds : FDs qu'on veut surveiller en écriture.
	 * except-fds : J'en sais rien.
	 * timeout : Structure contenant le temps que va attendre select avant de trouver un FD prêt.
	 * Si on met NULL, il attendra indéfiniment un FD. Il faut donc lui envoyé une structure initialisiée
	 * à 0 seconde et 0 useconde pour que se soit instantané.
	 */
	if(mblock)
		res = pselect(mfdmax + 1, &mfdset, nullptr, nullptr, nullptr, &morig_mask);
	else
		res = select(mfdmax + 1, &mfdset, nullptr, nullptr, nullptr);

	if (res < 0 && errno != EINTR) {
		perror ("select");
		throw IOException();
	}
}

void FDListener::blocksig() {
	mblock = true;
	sigset_t mask;

	sigemptyset (&mask);
	sigaddset (&mask, SIGTERM);
	sigaddset (&mask, SIGINT);

	if (sigprocmask(SIG_BLOCK, &mask, &morig_mask) < 0) {
		perror ("sigprocmask");
	}
}

bool FDListener::isFDReceiving(FDCommunication* FD) {
	return FD_ISSET(FD->getFD(), &mfdset);
}
