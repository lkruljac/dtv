#include <stdio.h>
//#include <directfb.h>
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

int main(int32_t argc, char** argv){
	
	//Argp
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return (1);
    }
	char* configFileName;
	configFileName = strdup(argv[1]);

	//Parsing config file
	printf("Parssing config file on path: \"%s\"\n\n", configFileName);
	if(loadConfigFile(configFileName) != 0){
		printf("Error during loading config file. Program is exiting now!\n");
		exit(1);	
	}
	volumeStatus.volume = 17;

	//Start stream
	//	Playing chanell from cfg
	//	Parsing PAT & PMT
	pthread_t thread_PlayStream;
	printf("Play stream thread called!\n");
	pthread_create(&thread_PlayStream, NULL, PlayStream, NULL);

	
	
	//Enable overlayer drawing
	
	//Start remote
	pthread_t thread_listenRemote;
	printf("Remote listen thread called!\n");
	pthread_create(&thread_listenRemote, NULL, listenRemote, NULL);

	pthread_join(thread_PlayStream, NULL);
	pthread_join(thread_listenRemote, NULL);

	

	return 0;
}
