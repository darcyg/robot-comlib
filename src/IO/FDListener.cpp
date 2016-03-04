/*
 * FDListener.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#include "FDListener.h"



void FDListener::signalHandler( int signum )
{
	std::cout << "Interrupt signal (" << signum << ") received.\n";
	exit_request = 1;

}


FDListener::FDListener() {
	mtimeout = nullptr;
	mfdmax = 0;
	mfdwatched = std::vector<FDCommunication*>();
	FD_ZERO(&mfdset);
	exit_request=0;
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

	sigset_t mask;
	sigset_t orig_mask;
	struct sigaction act;


	memset (&act, 0, sizeof(act));
	act.sa_handler = signalHandler;


	signal(SIGINT, signalHandler); // if the user interrupts the process ctrl+C
	signal(SIGTERM, signalHandler);// if the user kills the process

	/* This server should shut down on SIGTERM. */
	if (sigaction(SIGTERM, &act, 0)) {
		perror ("sigaction");
	}

	sigemptyset (&mask);
	sigaddset (&mask, SIGTERM);

	if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0) {
		perror ("sigprocmask");
	}

	while (!exit_request) {

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
		res = pselect(mfdmax + 1, &mfdset, nullptr, nullptr, nullptr, &orig_mask);
		if (res < 0 && errno != EINTR) {
			perror ("select");
			throw IOException();
		}
		else if (exit_request) {
			puts ("exit");
			break;
		}
		else if (res == 0)
			continue;
	}

}

bool FDListener::isFDReceiving(FDCommunication* FD) {
	return FD_ISSET(FD->getFD(), &mfdset);
}
