#include "pat.h"

#include "globals.h"
#include "streamplayer.h"

void *ParsePat(){
	
	printf("Parsing pat...\n");

	int result;
	/* Set filter to demux */
	pthread_mutex_lock(&statusMutex);
    result = Demux_Set_Filter(playerHandle, 0x0000, 0x00, &filterHandle);

    ASSERT_TDP_RESULT(result, "Demux_Set_Filter");
    
    /* Register section filter callback */
    result = Demux_Register_Section_Filter_Callback(mySecFilterCallback);
    ASSERT_TDP_RESULT(result, "Demux_Register_Section_Filter_Callback");
    
    /* Wait for a while to receive several PAT sections */
    patFlag = 0;
    while(!patFlag);

    /* Unegister section filter callback */
    result = Demux_Unregister_Section_Filter_Callback(mySecFilterCallback);
    ASSERT_TDP_RESULT(result, "Demux_Unregister_Section_Filter");
    /* Free filter */
    result = Demux_Free_Filter(playerHandle, filterHandle);
    ASSERT_TDP_RESULT(result, "Demux_Free_Filter");
	pthread_mutex_unlock(&statusMutex);
}


int32_t mySecFilterCallback(uint8_t *buffer)
{
    //printf("\n\nSection arrived!!!\n\n");
	parseBufferToPat(buffer, &pat);

	printPatTable(&pat);
    patFlag = 1;
	return 0;
}


void parseBufferToPat(uint8_t *buffer, PAT_TABLE *pat) {
	pat->table_id = buffer[0];
	
	pat->section_syntax_indicator = (buffer[1] & 0b10000000) >> 7;
	
	pat->reserved10 = (buffer[1] & 0b00110000) >> 4;


	pat->section_lenght = (buffer[1] & 0b00001111);
	pat->section_lenght <<= 8;
	pat->section_lenght += buffer[2];
	
	pat->transport_stream_id = buffer[3];
	pat->transport_stream_id <<= 8;
	pat->transport_stream_id += buffer[4];


	pat->reserved40 = (buffer[5] & 0b11000000) >> 6;

	pat->version_number = (buffer[5] & 0b00111110) >> 1;

	pat->current_next_indicator = (buffer[5] & 0b00000001);
	
	pat->section_number = buffer[6];

	pat->last_section_number = buffer[7];

	pat->programCounter = (pat->section_lenght - 9) / 4;
	pat->program = malloc(pat->programCounter * sizeof(PROGRAM));

	int i;
	for (i = 0; i < pat->programCounter; i++) {
		pat->program[i].program_number = buffer[8+(i*4)];
		pat->program[i].program_number <<= 8;
		pat->program[i].program_number += buffer[9+(i*4)];

		pat->program[i].reserved = (buffer[10 + (i*4)] & 0b11100000) >> 5;

		pat->program[i].pid = buffer[10 + (i*4)];
		pat->program[i].pid <<=8;
		pat->program[i].pid += buffer[11+(i*4)];
		pat->program[i].pid = (pat->program[i].pid & 0x1FFF);
	}
	

	pat->CRC_32 = buffer[8 + (i*4)] << 24;
	pat->CRC_32 += (buffer[9 + (i*4)] << 16);
	pat->CRC_32 += (buffer[10 + (i*4)] << 8);
	pat->CRC_32 += (buffer[11 + (i*4)]);

}


void printPatTable(PAT_TABLE *pat){
	
	printf("\nPAT_TABLE:\n");
	printf("\n\tTable_id: %d", pat->table_id);
	printf("\n\tSection syntax indicator: %d", pat->section_syntax_indicator);
	printf("\n\tReserved10: %d", pat->reserved10);
	printf("\n\tSection Lenght: %d", pat->section_lenght);
	printf("\n\tTransport stream ID: %d", pat->transport_stream_id);
	printf("\n\tReserved40: %d", pat->reserved40);
	printf("\n\tVersion number: %d", pat->reserved10);
	printf("\n\tCurrent next indicator: %d", pat->current_next_indicator);
	printf("\n\tSection number: %d", pat->section_number);
	printf("\n\tLast section number: %d", pat->last_section_number);
	printf("\n\tCRC: %d", pat->CRC_32);
	int i;
	for (i = 0; i < pat->programCounter; i++) {
		printf("\n\t\t Program on index: %d", i);
		printf("\n\t\t\tProgram number: %d", pat->program[i].program_number);
		printf("\n\t\t\tReserved: %d", pat->program[i].reserved);
		printf("\n\t\t\tPID: %d", pat->program[i].pid);
	}

	printf("\nEnd of PAT table\n");
}