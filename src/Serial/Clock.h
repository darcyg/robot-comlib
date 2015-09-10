/*
 * Clock.h
 *
 *  Created on: 12 avr. 2015
 *      Author: gabriel
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <time.h>

typedef struct Clock {
	struct timespec timestart; //Relatif au lancement du process
} Clock;


static inline void clock_reset(Clock* clock) {
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &(clock->timestart));
}

static inline double clock_getTime(Clock* clock) {
	struct timespec stop;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
	stop.tv_sec-=clock->timestart.tv_sec;
	stop.tv_nsec-=clock->timestart.tv_nsec;
	return (double)stop.tv_sec+(double)stop.tv_nsec/1000000000;
}

#endif /* CLOCK_H_ */
