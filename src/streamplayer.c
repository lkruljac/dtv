#include "streamplayer.h"

void* PlayStream(){
	
	int32_t result;

    struct timespec lockStatusWaitTime;
    struct timeval now;
    

    pmt = NULL;
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
  
    
    /* Initialize player (demux is a part of player) */
    result = Player_Init(&playerHandle);
	
    ASSERT_TDP_RESULT(result, "Player_Init");
    
    /* Open source (open data flow between tuner and demux) */
    result = Player_Source_Open(playerHandle, &sourceHandle);
    ASSERT_TDP_RESULT(result, "Player_Source_Open");
   	
	uint32_t audioPID = config.apid;
	uint32_t videoPID = config.vpid; 	

	tStreamType videoStreamType = VIDEO_TYPE_MPEG2;
	tStreamType audioStreamType = AUDIO_TYPE_MPEG_AUDIO;

	Player_Stream_Create(playerHandle, sourceHandle, videoPID, videoStreamType, &videoStreamHandle);
	Player_Stream_Create(playerHandle, sourceHandle, audioPID, audioStreamType, &audioStreamHandle);

    fflush(stdin);
    pthread_mutex_unlock(&statusMutex);
    printf("Press any key to stop\n");

    getchar();
	while(getchar() );
	
    /* Deinitialization */
    PlayStreamDeintalization();
		
}

void PlayStreamDeintalization(){
    
    int result;

    /* Close previously opened source */
    result = Player_Source_Close(playerHandle, sourceHandle);
    ASSERT_TDP_RESULT(result, "Player_Source_Close");
    /* Deinit player */
    result = Player_Deinit(playerHandle);
    ASSERT_TDP_RESULT(result, "Player_Deinit");
    
    /* Deinit tuner */
    result = Tuner_Deinit();
    ASSERT_TDP_RESULT(result, "Tuner_Deinit");
}

inline void textColor(int32_t attr, int32_t fg, int32_t bg)
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

void changePlayStreamOnChanell(int ChanellNumber){
   	
    Player_Stream_Remove(playerHandle, sourceHandle, videoStreamHandle);
	Player_Stream_Remove(playerHandle, sourceHandle, audioStreamHandle);

 
    uint32_t audioPID = program_mapHC[ChanellNumber].audioPID;
    //uint32_t audioPID = 103;
	//uint32_t videoPID = 201;
    uint32_t videoPID = program_mapHC[ChanellNumber].videoPID;
    //printf("Novi pidovi su %d i %d za kanal %d\n", audioPID, videoPID, chanelStatus.currentProgram);
	//tStreamType videoStreamType = program_map[ChanellNumber].videoType;
	//tStreamType audioStreamType = program_map[ChanellNumber].audioType;
    
    drawCurrentChanellFlag = 1;

    if(program_mapHC[ChanellNumber].radioFlag == 0){
        Player_Stream_Create(playerHandle, sourceHandle, videoPID, VIDEO_TYPE_MPEG2, &videoStreamHandle);
    }
    Player_Stream_Create(playerHandle, sourceHandle, audioPID, AUDIO_TYPE_MPEG_AUDIO, &audioStreamHandle); 
    
    drawForbidenContentFlag = program_mapHC[ChanellNumber].contentRank > config.rating;
    
}


