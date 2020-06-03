#ifndef MY_GLOBALS_H
#define	MY_GLOBALS_H

#include <stdint.h>
#include <pthread.h>

#define NUM_EVENTS  	5
#define NON_STOP    	1
/* error codes */
#define MY_NO_ERROR 		0
#define MY_ERROR			1

#define TRUE			1
#define	FALSE			0


struct volumeStatus{
	int volume;
	int volumeBackUp;
	int muteFlag;
}volumeStatus;

uint8_t defaultAudioPID;
uint8_t defaultVideoPID;

extern struct config{
	int freq;
	int bandwidth;
	char *module;
	int apid;
	int vpid;
	char *atype;
	char *vtype;
	int rating;
	int password;
}config;

extern pthread_cond_t statusCondition;
extern pthread_mutex_t statusMutex;

#endif