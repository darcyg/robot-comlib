/*
 * UARTserver.h
 *
 *  Created on: 12 sept. 2015
 *      Author: ethel
 */

#ifndef SERIAL_UARTSERVER_H_
#define SERIAL_UARTSERVER_H_

#include <sys/types.h>

#include <vector>
#include "UARTSerial.h"
#include "../IO/FDCommunication.h"
#include "../IO/FDListener.h"

class UARTServer : public UARTSerial {
public:
	UARTServer();
	virtual ~UARTServer();
	void launch(const std::string& device);
	bool isConnected();

	void run();

	class Events {
	public:
		virtual void onConnected(UARTServer* uart) = 0;
		virtual void onDisconnected(UARTServer* uart) = 0;
		virtual void onConnectionFailed(UARTServer* uart) = 0;
		virtual void onMessageReceived(UARTServer* uart, uint8_t buffer[], uint32_t len) = 0;
	};

	void setEvents(Events* events) {mevents = events;}
	void setFDListener(FDListener* listener) {mfdlistener = listener;}


private:
	using UARTSerial::open;
protected:
	Events* mevents;
	FDListener* mfdlistener;
};



#endif /* SERIAL_UARTSERVER_H_ */
