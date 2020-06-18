/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* pmt.h
*
* Purpose: Parsing stream sections to PMT
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

#ifndef PMT_H
#define PMT_H

#include "tdp_api.h"

#define AUDIO_ST 	(1)
#define VIDEO_ST	(2)

typedef struct PROGRAM_MAP{
	uint32_t videoPID;
	uint32_t audioPID;
	tStreamType videoType;
	tStreamType audioType;
	int radioFlag;
	int contentRank; 
}PROGRAM_MAP;

//TODO
//return 
//  0 - invalid type
//  1 - audio type
//  2 - video type
//  3 - titlovi
int getTypeOfStreamType(uint8_t type);


typedef struct STREAM{
	uint8_t stream_type;
	uint8_t reserved;
	uint16_t elementary_PID;
	uint8_t reserved2;
	uint16_t ES_info_lenght;

	uint16_t descriptor;
}STREAM;

typedef struct PMT_TABLE{
	uint8_t table_id;
	uint8_t section_syntax_indicator;
	uint8_t reserved1;
	uint16_t section_lenght;
	uint16_t program_number;
	uint8_t reserved2;
	uint8_t version_number;
	uint8_t current_next_indicator;
	uint8_t section_number;
	uint8_t last_section_number;
	uint8_t reserved3;
	uint16_t PCR_PID;
	uint8_t reserved4;
	uint16_t program_info_lenght;
	uint32_t CRC;
	
	void *descriptor;
	
	uint8_t streamCounter;
	STREAM *stream;
}PMT_TABLE;

void *ParsePmt();
int32_t myPMTSecFilterCallback(uint8_t *buffer);
void parseBufferToPmt(uint8_t *buffer, PMT_TABLE *pmt);
void printPmtTable(PMT_TABLE *pmt);


void PMT_to_ProgramMap(PMT_TABLE pmt, int index);
tStreamType getAudioType(int type);
tStreamType getVideoType(int type);


#endif