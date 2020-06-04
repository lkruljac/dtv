#include"remote.h"


#define EXIT    (10)
#define NOERROR (0)


void *listenRemote(){
    printf("Thread start here, now listening remote\n"); 
    const char* dev = "/dev/input/event0";
    char deviceName[20];
    struct input_event* eventBuf;
    uint32_t eventCnt;
    uint32_t i;
    
    inputFileDesc = open(dev, O_RDWR);
    if(inputFileDesc == -1)
    {
        printf("Error while opening device (%s) !", dev);
	    return -1;
    }
    
    ioctl(inputFileDesc, EVIOCGNAME(sizeof(deviceName)), deviceName);
	printf("RC device opened succesfully [%s]\n", deviceName);
    
    eventBuf = malloc(NUM_EVENTS * sizeof(struct input_event));
    if(!eventBuf)
    {
        printf("Error allocating memory !");
        return -1;
    }
    int exit = 0;
    while(NON_STOP && !exit)
    {
        /* read input eventS */
        if(getKeys(NUM_EVENTS, (uint8_t*)eventBuf, &eventCnt))
        {
			printf("Error while reading input events !");
			return;
		}
        int result;
        result = processKey(eventBuf);
        if(NOERROR == result){

        }
        else if(EXIT == result){
            exit = 1;
            printf("Exit from app\n");
            break;
        }
        else if(MY_ERROR == result){
            printf("Error\t while processing pressed Key\n");
        }
        else{

        }
		
    }

}

int32_t getKeys(int32_t count, uint8_t* buf, int32_t* eventsRead)
{
    int32_t ret = 0;
    
    /* read input events and put them in buffer */
    ret = read(inputFileDesc, buf, (size_t)(count * (int)sizeof(struct input_event)));
    if(ret <= 0)
    {
        printf("Error code %d", ret);
        return MY_ERROR;
    }
    /* calculate number of read events */
    *eventsRead = ret / (int)sizeof(struct input_event);
    
    return MY_NO_ERROR;
}



int processKey(struct input_event *eventBuf){
    printf("Key\t(%d)\t pressed..\tType:%d,\tValue:%d\n", eventBuf->code, eventBuf->type, eventBuf->value);
    int result;
    int retValue = MY_NO_ERROR;
    uint32_t volumeSTB;
    switch (eventBuf->code){

        case 102://exit
            retValue = EXIT;
            break;  
       	  
        case 63://volumeUp
            if(eventBuf->type == 1 && eventBuf->value == 0){
                if( volumeStatus.volume < 100){
                    volumeStatus.volume++;				
                }
            }
            printf("Volume:\t%d\n", volumeStatus.volume);
            Player_Volume_Get(playerHandle, &volumeSTB);
            result = Player_Volume_Set(playerHandle, MAX_VOLUME*((float)volumeStatus.volume/100));
            ASSERT_TDP_RESULT(result, "Volume set");
            Player_Volume_Get(playerHandle, &volumeSTB);
            printf("On: %d\n", volumeSTB);

            break;

        case 64://volumeDown
            if(eventBuf->type == 1 && eventBuf->value == 0){
                  if( volumeStatus.volume > 0){
                    volumeStatus.volume--;				
                }
            }
            printf("Volume:\t%d\n", volumeStatus.volume);
            Player_Volume_Get(playerHandle, &volumeSTB);
            Player_Volume_Get(playerHandle, &volumeSTB);
            printf("On: %d\n", volumeSTB);

            result = Player_Volume_Set(playerHandle,  MAX_VOLUME*((float)volumeStatus.volume/100));
            ASSERT_TDP_RESULT(result, "Volume set");
            break;

        case 60://Mute/Unmute
            if(eventBuf->type == 1 && eventBuf->value == 0){
                //Unmute
                if(volumeStatus.volume == 0 ){
                    volumeStatus.volume = volumeStatus.volumeBackUp;
                    printf("\tUnmuted\n");
                    result = Player_Volume_Set(playerHandle,  MAX_VOLUME*((float)volumeStatus.volume/100));
                    ASSERT_TDP_RESULT(result, "Volume set");
                }
                //Mute					
                else{
                    printf("\tMuted\n");
                    volumeStatus.volumeBackUp = volumeStatus.volume;					
                    volumeStatus.volume = 0;
                    result = Player_Volume_Set(playerHandle,  MUTE);
                    ASSERT_TDP_RESULT(result, "Volume set");
                }									
            }
            printf("Volume:\t%d\n", volumeStatus.volume);
            break;
        
        default:
            if(eventBuf->code >= 0 || eventBuf->code <= 9){
                //changeChanel(eventBuf->code);
            }
            retValue = MY_ERROR;
            break;
    }

    return retValue;
}

