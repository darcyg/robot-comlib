/*
 * Buffer.c
 *
 *  Created on: 20 avr. 2015
 *      Author: gabriel
 */

#include "Buffer.h"

#define readput(name, type) \
	void buffer_put_##name (Buffer* buffer, type data) { \
		buffer_put(buffer, &data, 1, sizeof(type)); \
	} \
	type buffer_get_##name (Buffer* buffer) { \
		type data; \
		buffer_get(buffer, &data, 1, sizeof(type)); \
		return data; \
	}

void buffer_init(Buffer* buffer) {
	buffer->size = 0;
}

int buffer_ready(Buffer* buffer) {
	return buffer->size>0;
}

void buffer_put(Buffer* buffer, const void* data, size_t sizearray, size_t sizetype) {
	sizearray*=sizetype;
	uint32_t size = buffer->size;
	size+=sizearray;
	if(size>BUFSIZE) {
		printf("Attention : Vous envoyez plus de donnees dans le buffer qu'il ne peut en contenir\n"
				"\tLes donnees sont tronquees\n");
		sizearray-=(size-BUFSIZE);
		size = BUFSIZE;
	}

	memcpy(buffer->buffer+buffer->size, data, sizearray);
	buffer->size = size;
}

void buffer_get(Buffer* buffer, void* data, size_t sizearray, size_t sizetype) {
	sizearray*=sizetype;
	uint32_t size = buffer->size;
	size-=sizearray;
	if(size<0) {
		printf("Attention : Vous charger plus de donnees du buffer qu'il ne contient\n"
				"\tLes donnees sont tronquees\n");
		sizearray+=size;
		size = 0;
	}

	memcpy(data, buffer->buffer, sizearray);
	memmove(buffer->buffer, buffer->buffer+sizearray, buffer->size-sizearray);
	buffer->size = size;
}

readput(int, int)
readput(float, float)
readput(uint8, uint8_t)
readput(double, double)

