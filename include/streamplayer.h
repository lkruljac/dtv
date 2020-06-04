#ifndef STREAM_PLAYER_H
#define STREAM_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "errno.h"
#include "tdp_api.h"
#include <stdint.h>

#include "globals.h"
#include "pat.h"



inline void textColor(int32_t attr, int32_t fg, int32_t bg);

#define ASSERT_TDP_RESULT(x,y)  if(NO_ERROR == x) \
                                    printf("%s success\n", y); \
                                else{ \
                                    textColor(1,1,0); \
                                    printf("%s fail\n", y); \
                                    textColor(0,7,0); \
                                    return -1; \
                                }

int32_t myPrivateTunerStatusCallback(t_LockStatus status);
int32_t mySecFilterCallback(uint8_t *buffer);

int32_t myStreamFilterCallback(uint8_t *buffer);

void* PlayStream();
void PlayStreamDeintalization();

#endif