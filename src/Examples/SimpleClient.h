/*
 * SimpleClient.h
 *
 *  Created on: Sep 10, 2015
 *      Author: gabriel
 */

#ifndef EXAMPLES_SIMPLECLIENT_H_
#define EXAMPLES_SIMPLECLIENT_H_

#include <iostream>

#include "../Socket/Client/TCPClient.h"

class SimpleClient : public TCPClient, TCPClient::Events {
public:
	SimpleClient();

	virtual void onConnected() const;
	virtual void onConnectionFailed() const;
	virtual void onDisconnected() const;
	virtual void onMessageReceived(uint8_t buffer[], uint8_t len) const;
};

#endif /* EXAMPLES_SIMPLECLIENT_H_ */
