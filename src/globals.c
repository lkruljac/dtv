#include "globals.h"


struct volumeStatus volumeStatus;

uint8_t defaultAudioPID;
uint8_t defaultVideoPID;

struct config config;

pthread_cond_t statusCondition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t statusMutex = PTHREAD_MUTEX_INITIALIZER;