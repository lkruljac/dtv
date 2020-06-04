#include "globals.h"


struct volumeStatus volumeStatus;


uint8_t defaultAudioPID;
uint8_t defaultVideoPID;

struct config config;

pthread_cond_t statusCondition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t statusMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t thread_PlayStream;
pthread_t thread_ParsePat;
pthread_t thread_ParsePmt;

PAT_TABLE pat;
PMT_TABLE *pmt = NULL;
int parserProgramIndex = 0;

uint32_t playerHandle = 0;
uint32_t sourceHandle = 0;
uint32_t filterHandle = 0;

uint32_t filterHandelArray[8] = {0};

extern	uint32_t audioStreamHandle = 0;
extern	uint32_t videoStreamHandle = 0;

int patFlag = 0;
int pmtFlag = 0;
