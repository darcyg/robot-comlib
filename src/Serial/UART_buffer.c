/*
 * UART_buffer.c
 *
 *  Created on: Apr 13, 2015
 *      Author: julien
 */


#include "UART_buffer.h"

void incReadPtr(UART_BUFFER* buffer);
void incWritePtr(UART_BUFFER* buffer);


void initUARTBuffer(UART_BUFFER *buffer)
{
	buffer->readptr=0;
	buffer->writeptr=0;
}

int emptyBuffer(UART_BUFFER* buffer)
{
	if(buffer->readptr == buffer->writeptr)
	{
		return 1;
	}
	return 0;
}
int fullBuffer(UART_BUFFER* buffer)
{
	if(buffer->writeptr==buffer->readptr-1)
	{
		return 1;
	}
	else if(buffer->readptr==0 && buffer->writeptr==UART_BUFFER_MAX_SIZE-1)
	{
		return 1;
	}
	return 0;
}

void incReadPtr(UART_BUFFER* buffer)
{
	buffer->readptr++;
	if(buffer->readptr==UART_BUFFER_MAX_SIZE)
	{
		buffer->readptr=0;
	}
}
void incWritePtr(UART_BUFFER* buffer)
{
	buffer->writeptr++;
	if(buffer->writeptr==UART_BUFFER_MAX_SIZE)
	{
		buffer->writeptr=0;
	}
}
int readBuffer(UART_BUFFER* buffer,uint8_t *output,unsigned int nread)
{
	int n=0;
	if(emptyBuffer(buffer))
	{
		return 0;
	}
	while(nread > 0 && !emptyBuffer(buffer))
	{
		*output=buffer->buffer[buffer->readptr];
		incReadPtr(buffer);
		output++;
		nread--;
		n++;
	}
	return n;
}

int writeBuffer(UART_BUFFER* buffer,uint8_t *input,unsigned int nwrite)
{
	int n=0;
	if(fullBuffer(buffer))
	{
		return 0;
	}
	while(nwrite > 0 && !fullBuffer(buffer))
	{
		buffer->buffer[buffer->writeptr]=*input;
		incWritePtr(buffer);
		input++;
		nwrite--;
		n++;
	}
	return n;
}
