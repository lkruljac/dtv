/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* pat.h
*
* Purpose: Parsing stream sections to PAT
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

#define PAT_H

#include "tdp_api.h"

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

void *ParsePat();
void parseBufferToPat(uint8_t *buffer, PAT_TABLE *pat);
void printPatTable(PAT_TABLE *pat);
int32_t mySecFilterCallback(uint8_t *buffer);

#endif