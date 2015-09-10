/*
 * UART_buffer.h
 *
 *  Created on: Apr 13, 2015
 *      Author: julien
 */

#ifndef UART_BUFFER_H_
#define UART_BUFFER_H_

#include <stdint.h>

#define UART_BUFFER_MAX_SIZE 255

typedef struct UART_BUFFER{
	uint8_t buffer[UART_BUFFER_MAX_SIZE];
	unsigned int readptr;
	unsigned int writeptr;
}UART_BUFFER;




void initUARTBuffer(UART_BUFFER* buffer);
int emptyBuffer(UART_BUFFER* buffer);
int fullBuffer(UART_BUFFER* buffer);


int writeBuffer(UART_BUFFER* buffer,uint8_t *input,unsigned int nwrite);
int readBuffer(UART_BUFFER* buffer,uint8_t *output,unsigned int nread);



#endif /* UART_BUFFER_H_ */
