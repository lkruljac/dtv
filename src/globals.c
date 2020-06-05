#include "globals.h"


struct volumeStatus volumeStatus;

struct chanelStatus	chanelStatus;

uint8_t defaultAudioPID;
uint8_t defaultVideoPID;


 PROGRAM_MAP *program_map = NULL;

PROGRAM_MAP program_mapHC[8] = {

	//0
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//1
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//2
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//3
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//4
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//5
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//6
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	},

	//7
	{
		.audioPID = 103,
		.videoPID= 101,
		.audioType = AUDIO_TYPE_MPEG_AUDIO,
		.videoType = VIDEO_TYPE_MPEG2,
	}


};

struct config config;

pthread_cond_t statusCondition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t statusMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t thread_PlayStream;
pthread_t thread_Graphic;
pthread_t thread_ParsePat;
pthread_t thread_ParsePmt;

PAT_TABLE pat;
PMT_TABLE *pmt = NULL;
int parserProgramIndex = 0;

uint32_t playerHandle = 0;
uint32_t sourceHandle = 0;
uint32_t filterHandle = 0;

uint32_t filterHandelArray[8] = {0};

uint32_t audioStreamHandle = 0;
uint32_t videoStreamHandle = 0;

int patFlag = 0;
int pmtFlag = 0;

IDirectFBSurface *primary = NULL;
IDirectFB *dfbInterface = NULL;
int screenWidth = 0;
int screenHeight = 0;
DFBSurfaceDescription surfaceDesc;
