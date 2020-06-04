#ifndef MY_GLOBALS_H
#define	MY_GLOBALS_H

#include <stdint.h>
#include <pthread.h>
#include "pat.h"
#include "pmt.h"

#define NUM_EVENTS  	5
#define NON_STOP    	1
/* error codes */
#define MY_NO_ERROR 		0
#define MY_ERROR			1

#define TRUE			1
#define	FALSE			0


struct volumeStatus{
	uint32_t volume;
	uint32_t volumeBackUp;
	uint32_t muteFlag;
}volumeStatus;




#define DEFAULTVOLUME	(-100000000)
#define MUTE			(0)
#define MAX_VOLUME		(599999999)
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

extern PAT_TABLE pat;
extern PMT_TABLE *pmt;
extern int parserProgramIndex;

extern uint32_t playerHandle;
extern uint32_t sourceHandle;
extern uint32_t filterHandle;
extern uint32_t filterHandelArray[8];

extern	uint32_t audioStreamHandle;
extern	uint32_t videoStreamHandle;

extern int patFlag;
extern int pmtFlag;

extern int pmtTableParsedFlag;

#endif