/*
 * Buffer.h
 *
 *  Created on: 20 avr. 2015
 *      Author: gabriel
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFSIZE 64

typedef struct Buffer {
	uint8_t buffer[BUFSIZE];
	uint32_t size;
} Buffer;

void buffer_init(Buffer* buffer);

int buffer_ready(Buffer* buffer);



void buffer_put(Buffer* buffer, const void* data, size_t sizearray, size_t sizetype);

void buffer_get(Buffer* buffer, void* data, size_t sizearray, size_t sizetype);



int buffer_get_int(Buffer* buffer);

void buffer_put_int(Buffer* buffer, int data);

float buffer_get_float(Buffer* buffer);

void buffer_put_float(Buffer* buffer, float data);

uint8_t buffer_get_uint8(Buffer* buffer);

void buffer_put_uint8(Buffer* buffer, uint8_t data);

double buffer_get_double(Buffer* buffer);

void buffer_put_double(Buffer* buffer, double data);

#endif /* BUFFER_H_ */
