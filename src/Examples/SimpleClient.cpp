/*
 * SimpleClient.cpp
 *
 *  Created on: Sep 10, 2015
 *      Author: gabriel
 */

#include "SimpleClient.h"

SimpleClient::SimpleClient() : TCPClient() {
	setEvents(this);
}

void SimpleClient::onConnected() const {
	std::cout << "Connected" << std::endl;
}

void SimpleClient::onConnectionFailed() const {
	std::cout << "Connection failed" << std::endl;
}

void SimpleClient::onDisconnected() const {
	std::cout << "Disconnected" << std::endl;
}

void SimpleClient::onMessageReceived(uint8_t buffer[], uint8_t len) const {
	std::cout << "New message ! Length : " << (int)len << std::endl;
}
