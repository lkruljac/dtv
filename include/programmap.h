/*
#ifndef PROGRAMMAP_H
#define PROGRAMMAP_H

#include <stdint.h>


#define AUDIO_ST 	(1)
#define VIDEO_ST	(2)

typedef struct PROGRAM_MAP{
	uint32_t videoPID;
	uint32_t audioPID;
	t_StreamType videoType;
	t_StreamType audioType;
}PROGRAM_MAP;

//TODO
//return 
//  0 - invalid type
//  1 - audio type
//  2 - video type
//  3 - titlovi
int getTypeOfStreamType(uint8_t type);



#endif
*/