#include "pat.h"

#include "globals.h"
#include "streamplayer.h"

void *ParsePmt(){
	printf("\nNow parsing pmts in separated thread...\n");
	int result;
    pmt = malloc(pat.programCounter * sizeof(PMT_TABLE));
	uint32_t patFilterHandle;
    int programIndex;
    for(programIndex=1; programIndex<pat.programCounter; programIndex++){
		
	
        
		parserProgramIndex = programIndex;
        pmtFlag = 0;
        printf("\n\tProgram index: %d\n", programIndex);
		pthread_mutex_lock(&statusMutex);
        /* Set filter to demux */
		printf("\nTrying to filter progroma with pid: \t%d\n", pat.program[programIndex].pid);
        result = Demux_Set_Filter(playerHandle, (uint32_t) pat.program[programIndex].pid, 0x02, &patFilterHandle);
        ASSERT_TDP_RESULT(result, "Demux_Set_Filter-PMT set");
        /* Register section filter callback */
        result = Demux_Register_Section_Filter_Callback(myPMTSecFilterCallback);
        ASSERT_TDP_RESULT(result, "Demux_Register_Stream_Filter_Callback-PMT set");

      
        //wait to finish pmt
        while(pmtFlag == 0){
			//printf("Ovdje sam\n");
        };

			

        /* Unegister section filter callback */
        result = Demux_Unregister_Section_Filter_Callback(myPMTSecFilterCallback);
        ASSERT_TDP_RESULT(result, "Demux_Register_Stream_Filter_Callback-PMT done");
        /* Free filter */
        result = Demux_Free_Filter(playerHandle, patFilterHandle);
        ASSERT_TDP_RESULT(result, "Demux_Free_Filter-PMT done");

   		pthread_mutex_unlock(&statusMutex);
     
    }
}

int32_t myPMTSecFilterCallback(uint8_t *buffer)
{
    printf("\n\nSection arrived!!!\n\n");
	parseBufferToPmt(buffer, &pmt[parserProgramIndex]);
    printf("\n#######\nPMT number: %d\n#######\n", parserProgramIndex);
    printPmtTable(&pmt[parserProgramIndex]);
    pmtFlag = 1;
	return 0;
}


void printPmtTable(PMT_TABLE *pmt){
    printf("\nPMT:\n");
    printf("Table id:\t%d\n", pmt->table_id);
    printf("Section syntax indicator:\t%d\n", pmt->section_syntax_indicator);
    printf("Reserved1:\t%d\n", pmt->reserved1);
    printf("Section lenght:\t%d\n", pmt->section_lenght);
    printf("Program number:\t%d\n", pmt->program_number);
    printf("Reserved2:\t%d\n", pmt->reserved2);
    printf("Version number:\t%d\n", pmt->version_number);
    printf("Current next indicator:\t%d\n", pmt->current_next_indicator);
    printf("Section number\t%d\n", pmt->section_number);
    printf("Last section number:\t%d\n", pmt->last_section_number);
    printf("Reserved3:\t%d\n", pmt->reserved3);
    printf("PCR PID:\t%d\n", pmt->PCR_PID);
    printf("Reserved4:\t%d\n", pmt->reserved4);
    printf("Prorgram info lenght:\t%d\n", pmt->program_info_lenght);
    printf("CRC:\t%d\n", pmt->CRC);

    printf("Number of streams:\t%d\n", pmt->streamCounter);

    int i;
    for(i=0; i<pmt->streamCounter; i++){
        printf("\n\t\t#########\n\t\tSTREAM number: %d\n\t\t#########\n\n", i);
        printf("\t\t\tElemntaryPID:\t%d\n", pmt->stream[i].elementary_PID);
        printf("\t\t\tStream_type:\t%d\n", pmt->stream[i].stream_type);
        printf("\t\t\tReservd:\t%d\n", pmt->stream[i].reserved);
        printf("\t\t\tES inof lenght:\t%d\n", pmt->stream[i].ES_info_lenght);
        printf("\t\t\tReserved2:\t%d\n", pmt->stream[i].reserved2);
        printf("\t\t\tDescriptor:\t%d\n", pmt->stream[i].descriptor);
    }
    printf("End of PMT table\n");
    
    
}


void parseBufferToPmt(uint8_t *buffer, PMT_TABLE *pmt){
    pmt->table_id = buffer[0];
    
    pmt->section_syntax_indicator = (buffer[1] & 0b10000000) >> 7;
    
    pmt->reserved1 = (buffer[1] & 0b01100000) >> 5;
    
    pmt->section_lenght = (buffer[1] & 0b00001111);
    pmt->section_lenght <<=8;
    pmt->section_lenght += buffer[2];

    pmt->program_number = buffer[3];
    pmt->program_number <<=8;
    pmt->program_number += buffer[4];

    pmt->reserved2 = (buffer[5] & 0b11000000) >> 6;

    pmt->version_number = (buffer[5] & 0b00111110) >> 1;

    pmt->current_next_indicator =  (buffer[5] & 0b00000001);

    pmt->section_number = buffer[6];

    pmt->last_section_number = buffer[7];

    pmt->reserved3 = (buffer[8] & 0b11100000) >> 5;

    pmt->PCR_PID = (buffer[8] & 0b00011111);
    pmt->PCR_PID <<=8;
    pmt->PCR_PID += buffer[9];

    pmt->reserved4 = (buffer[10] & 0b11110000) >> 4;

    pmt->program_info_lenght = (buffer[10] & 0b00001111);
    pmt->program_info_lenght <<=8;
    pmt->program_info_lenght += buffer[11];

    /*
    int descriptorBytSize = pmt->program_info_lenght / 8;
    if(descriptorBytSize < (float)(pmt->program_info_lenght/8)){
        descriptorBytSize+=1;
    }
    pmt->descriptor = malloc(sizeof (descriptorBytSize));
    pmt->descriptor = buffer[12] & 
    */

    int loopBitSize = pmt->section_lenght - 9 - 4; //if descriptor is size 0
    int streamMaxNumber = loopBitSize/5;
    pmt->stream = malloc(sizeof(STREAM)*streamMaxNumber);
    
    int streamIndexBit = 0;
    pmt->streamCounter = 0;
    while(streamIndexBit < loopBitSize){

        pmt->stream[pmt->streamCounter].stream_type = buffer[12 + pmt->program_info_lenght + streamIndexBit];
        
        pmt->stream[pmt->streamCounter].elementary_PID = (((buffer[13 + pmt->program_info_lenght + streamIndexBit] << 8) + (buffer[14 + pmt->program_info_lenght + streamIndexBit])) & 0x1FFF); //13 bits

        pmt->stream[pmt->streamCounter].ES_info_lenght = (((buffer[15 + pmt->program_info_lenght + streamIndexBit] << 8) + (buffer[16 + pmt->program_info_lenght + streamIndexBit])) & 0x0FFF);  //12 bits

        pmt->stream[pmt->streamCounter].descriptor =  buffer[17 + pmt->program_info_lenght + streamIndexBit];

        streamIndexBit = 5 + pmt->stream[pmt->streamCounter].ES_info_lenght;
        pmt->streamCounter++;
    }
    pmt->CRC = buffer[12 + pmt->program_info_lenght + streamIndexBit];

}