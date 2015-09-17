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

	void run();
	void launch(const std::string& device);
	bool isConnected();

	class Events {
	public:
		virtual void onConnected() const = 0;
		virtual void onDisconnected() const = 0;
		virtual void onConnectionFailed() const = 0;
		virtual void onMessageReceived(uint8_t buffer[], uint8_t len) const = 0;
	};

	void setEvents(Events* events) {mevents = events;}
	void setFDListener(FDListener* listener) {mfdlistener = listener;}


private:
protected:
	Events* mevents;
	FDListener* mfdlistener;
};



#endif /* SERIAL_UARTSERVER_H_ */
