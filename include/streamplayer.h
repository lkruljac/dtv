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
typedef struct PROGRAM{
	uint16_t program_number;
	uint8_t reserved;
	uint16_t pid;
}PROGRAM;

typedef struct PAT_TABLE{
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved10;
	uint16_t section_lenght;
	uint16_t transport_stream_id;
	uint8_t reserved40;
	uint8_t	version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint32_t CRC_32;
	
	int programCounter;

	PROGRAM *program;
}PAT_TABLE;

static inline void textColor(int32_t attr, int32_t fg, int32_t bg);

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


void* PlayStream();

void parseBufferToPat(uint8_t *buffer, PAT_TABLE *pat);
void printPatTable(PAT_TABLE *pat);


#endif