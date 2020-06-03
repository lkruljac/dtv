#include "streamplayer.h"

void* PlayStream(){
	
	int32_t result;

    uint32_t filterHandle = 0;

    struct timespec lockStatusWaitTime;
    struct timeval now;
    


    gettimeofday(&now,NULL);
    lockStatusWaitTime.tv_sec = now.tv_sec+10;
    
    /* Initialize tuner */
    result = Tuner_Init();
    ASSERT_TDP_RESULT(result, "Tuner_Init");
    
    /* Register tuner status callback */
    result = Tuner_Register_Status_Callback(myPrivateTunerStatusCallback);
    ASSERT_TDP_RESULT(result, "Tuner_Register_Status_Callback");
    
    /* Lock to frequency */
    result = Tuner_Lock_To_Frequency(818000000, 8, DVB_T);
    ASSERT_TDP_RESULT(result, "Tuner_Lock_To_Frequency");
    
    pthread_mutex_lock(&statusMutex);
    if(ETIMEDOUT == pthread_cond_timedwait(&statusCondition, &statusMutex, &lockStatusWaitTime))
    {
        printf("\n\nLock timeout exceeded!\n\n");
        return -1;
    }
    pthread_mutex_unlock(&statusMutex);
    
    /* Initialize player (demux is a part of player) */
    result = Player_Init(&playerHandle);
	
    ASSERT_TDP_RESULT(result, "Player_Init");
    
    /* Open source (open data flow between tuner and demux) */
    result = Player_Source_Open(playerHandle, &sourceHandle);
    ASSERT_TDP_RESULT(result, "Player_Source_Open");
   	
	uint32_t audioPID = 103;
	uint32_t videoPID = 101; 	

	tStreamType videoStreamType = VIDEO_TYPE_MPEG2;
	tStreamType audioStreamType = AUDIO_TYPE_MPEG_AUDIO;

	Player_Stream_Create(playerHandle, sourceHandle, videoPID, videoStreamType, &videoStreamHandle);
	Player_Stream_Create(playerHandle, sourceHandle, audioPID, audioStreamType, &audioStreamHandle);

	

    /* Set filter to demux */
    result = Demux_Set_Filter(playerHandle, 0x0000, 0x00, &filterHandle);
    ASSERT_TDP_RESULT(result, "Demux_Set_Filter");
    
    /* Register section filter callback */
    result = Demux_Register_Section_Filter_Callback(mySecFilterCallback);
    ASSERT_TDP_RESULT(result, "Demux_Register_Section_Filter_Callback");
    
    /* Wait for a while to receive several PAT sections */
    fflush(stdin);
    
    printf("Press any key to stop\n");
	getchar();
    

	/* Deinitialization */
    
    /* Free demux filter */
    result = Demux_Free_Filter(playerHandle, filterHandle);
    ASSERT_TDP_RESULT(result, "Demux_Free_Filter");
    
    /* Close previously opened source */
    result = Player_Source_Close(playerHandle, sourceHandle);
    ASSERT_TDP_RESULT(result, "Player_Source_Close");
    Player_Volume_Set(playerHandle, DEFAULTVOLUME);
    /* Deinit player */
    result = Player_Deinit(playerHandle);
    ASSERT_TDP_RESULT(result, "Player_Deinit");
    
    /* Deinit tuner */
    result = Tuner_Deinit();
    ASSERT_TDP_RESULT(result, "Tuner_Deinit");
	
	
	
}

static inline void textColor(int32_t attr, int32_t fg, int32_t bg)
{
   char command[13];

   /* Command is the control command to the terminal */
   sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
   printf("%s", command);
}


int32_t myPrivateTunerStatusCallback(t_LockStatus status)
{
    if(status == STATUS_LOCKED)
    {
        pthread_mutex_lock(&statusMutex);
        pthread_cond_signal(&statusCondition);
        pthread_mutex_unlock(&statusMutex);
        printf("\n\n\tCALLBACK LOCKED\n\n");
    }
    else
    {
        printf("\n\n\tCALLBACK NOT LOCKED\n\n");
    }
    return 0;
}

int32_t mySecFilterCallback(uint8_t *buffer)
{
    //printf("\n\nSection arrived!!!\n\n");
	parseBufferToPat(buffer, &pat);

	//printPatTable(&pat);
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

		pat->program[i].pid = (buffer[10 + (i*4)] & 0b00011111);
		pat->program[i].pid <<=8;
		pat->program[i].pid += buffer[11+(i*4)];
	}
	

	pat->CRC_32 = buffer[8 + (i*4)] << 24;
	pat->CRC_32 += (buffer[9 + (i*4)] << 16);
	pat->CRC_32 += (buffer[10 + (i*4)] << 8);
	pat->CRC_32 += (buffer[11 + (i*4)]);
}

void printPatTable(PAT_TABLE *pat){
	
	printf("PAT_TABLE:\n");
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

	printf("\nEnd of PAT table");
}
