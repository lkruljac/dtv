#include <stdio.h>
#include <directfb.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <pthread.h>


#include "remote.h"
#include "configTool.h"
#include "streamplayer.h"
#include "pat.h"
#include "pmt.h"
#include "graphic.h"

int main(int32_t argc, char** argv){
	
	//Argp
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return (1);
    }
	char* configFileName;
	configFileName = strdup(argv[1]);

	//Start graphic
	printf("Grahpic thread called!\n");
	pthread_create(&thread_Graphic, NULL, GraphicThread, NULL);


	//Parsing config file
	printf("Parssing config file on path: \"%s\"\n\n", configFileName);
	if(loadConfigFile(configFileName) != 0){
		printf("Error during loading config file. Program is exiting now!\n");
		exit(1);	
	}
	//Init global variables
	volumeStatus.volume = 10;
	chanelStatus.currentProgram = 0;
	chanelStatus.startProgramNumber = 0;

	//	Start Stream
	//	Playing chanell from cfg
	printf("Play stream thread called!\n");
	pthread_create(&thread_PlayStream, NULL, PlayStream, NULL);

	//Start remote
	pthread_t thread_listenRemote;
	printf("Remote listen thread called!\n");
	pthread_create(&thread_listenRemote, NULL, listenRemote, NULL);

	//	Wait for player initialization
	while(playerHandle == 0){

	}
	//	Parse PAT
	printf("Parse PAT thread called!\n");
	pthread_create(&thread_ParsePat, NULL, ParsePat, NULL);
	
	
	//	Wait for PAT parser
	while(patFlag == 0){

	}
	pthread_join(thread_ParsePat, NULL);
	
	//	Parse PMTs
	printf("Parse PMTs thread called!\n");
	pthread_create(&thread_ParsePmt, NULL, ParsePmt, NULL);
	pthread_join(thread_ParsePmt, NULL);
	
	//Enable overlayer drawing


	pthread_join(thread_PlayStream, NULL);
	pthread_join(thread_listenRemote, NULL);


	return 0;
}
