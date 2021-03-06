/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* globals.h
*
* Purpose: Decalration of global(most of them extern) variables
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/



#ifndef MY_GLOBALS_H
#define	MY_GLOBALS_H

#include <stdint.h>
#include <pthread.h>
#include "pat.h"
#include "pmt.h"
#include "programmap.h"
#include <directfb.h>

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

struct chanelStatus{
	int currentProgram;
	int numberOfPrograms;
	int startProgramNumber;
	int endProgamNumber;
}chanelStatus;



#define MUTE			(0)
#define MAX_VOLUME		(0x7FFFFFFF)
uint8_t defaultAudioPID;
uint8_t defaultVideoPID;

extern PROGRAM_MAP *program_map;
extern PROGRAM_MAP program_mapHC[8];

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

extern pthread_t thread_PlayStream;
extern pthread_t thread_Graphic;
extern pthread_t thread_ParsePat;
extern pthread_t thread_ParsePmt;

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
extern int allPmtflag;

extern IDirectFBSurface *primary;
extern IDirectFB *dfbInterface;
extern int screenWidth;
extern int screenHeight;
extern DFBSurfaceDescription surfaceDesc;
extern IDirectFBFont *fontInterface;
extern DFBFontDescription fontDesc;

extern int drawVolumeFlag;
extern int drawForbidenContentFlag;
extern int drawCurrentChanellFlag;
extern int listenPwd;
extern int pwd;
#endif