/*
#include"programmap.h"
#include"globals.h"

//TODO
//return 
//  0 - invalid type
//  1 - audio type
//  2 - video type
//  3 - titlovi
int getTypeOfStreamType(uint8_t type){
    
    int returnValue = 0;
    //video
    if(type == 0x01
        || type == 0x02 
        || type == 0x10
        || type == 0x1b
        || type == 0x24)
    {
        returnValue = VIDEO_ST;
    }
    //audio
    else if(type == 0x03
        || type == 0x04 
        || type == 0x0F
        || type == 0x83
        || type == 0x84
        || type == 0x85)
    {
        returnValue = AUDIO_ST;
    }
	else{
		printf("\n#########\t%d je nista od navedneog############\n");
	}
    //TODO
    //rest
    return returnValue;

}

*/
