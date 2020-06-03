#ifndef PAT_H
#define PAT_H

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


#endif