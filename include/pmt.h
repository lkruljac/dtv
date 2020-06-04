#ifndef PMT_H
#define PMT_H

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


#endif