/*
 * FDListener.h
 *
 *  Created on: Aug 28, 2015
 *      Author: gabriel
 */

#ifndef FDLISTENER_H_
#define FDLISTENER_H_

#include <iostream>

#include <sys/select.h>

#include <vector>
#include <signal.h>

#include "FDCommunication.h"



class FDListener {
public:
	FDListener();

	void addFD(FDCommunication* newFD);
	void remFD(FDCommunication* FD);

	void listen() throw(IOException);

	void blocksig();

	bool isFDReceiving(FDCommunication* FD);


protected:
private:
	fd_set mfdset; //Stocke les files descriptors (FDs) à survveiller.
	std::vector<FDCommunication*> mfdwatched;
	sigset_t morig_mask;
	int mfdmax; //File descriptor ayant le plus grand numéro.
	timeval* mtimeout;
	bool mblock;
};

#endif /* FDLISTENER_H_ */
