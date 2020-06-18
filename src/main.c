/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* main.c
*
* Purpose: Calling big functions and creating threads
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/



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
	//Parsing config filename recived from main arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"config_filename.cfg\"\n", argv[0]);
        return (1);
    }
	char* configFileName;
	configFileName = strdup(argv[1]);


	//Start graphic
	//Enable overlayer drawing
	//Before anything, draw logo on screen as sign that TV is turned on
	//In same thread listen other possible flags for drawing on screen(Volume change, Program Change, Forbiden Content)
	printf("Grahpic thread called!\n");
	pthread_create(&thread_Graphic, NULL, GraphicThread, NULL);


	//Parsing config file
	//In given config file (from main arguments), look for paramtars described in struct config(globals.h)
	printf("Parssing config file on path: \"%s\"\n\n", configFileName);
	if(loadConfigFile(configFileName) != 0){
		printf("Error during loading config file. Program is exiting now!\n");
		exit(1);	
	}


	//Init global variables
	volumeStatus.volume = 10;
	chanelStatus.currentProgram = 0;
	chanelStatus.startProgramNumber = 0;
	chanelStatus.endProgamNumber = 7;

	
	//	Start Stream
	//	Playing chanel described in config file
	//  Listen "press any key to exti.."
	printf("Play stream thread called!\n");
	pthread_create(&thread_PlayStream, NULL, PlayStream, NULL);


	// Start remote
	// Thread listen preesed keys from remote
	// Call functions on(mute, volum up/down, program up/down, program key)
	// Set flags for graphic if speciffic key is pressed 
	pthread_t thread_listenRemote;
	printf("Remote listen thread called!\n");
	pthread_create(&thread_listenRemote, NULL, listenRemote, NULL);


	// Wait for player initialization
	// In PlayStream thread hanndler for player is initialized with value 0
	// When PlayStream thread set up stream, player handler will bi change to value other than 0
	// This is sign to start parsing PAT
	while(playerHandle == 0){

	}
	//	Parse PAT
	printf("Parse PAT thread called!\n");
	pthread_create(&thread_ParsePat, NULL, ParsePat, NULL);
	
	
	//	Wait for PAT parser
	//  When PAT is parsed, there is flag that will be changed to 1, so if patFlag != 0, main go on 
	while(patFlag == 0){

	}
	// Now pat is parsed, ParsePat thread is no needed anymore
	pthread_join(thread_ParsePat, NULL);
	
	// Parse PMTs
	// Now pat is parsed, it is time to parse PMT
	printf("Parse PMTs thread called!\n");
	pthread_create(&thread_ParsePmt, NULL, ParsePmt, NULL);
	
	// Wait for all pmt to be parsed
	while(allPmtFlag == 0){

	}
	// Finish ParsePmt thread
	pthread_join(thread_ParsePmt, NULL);
	

	
	pthread_join(thread_PlayStream, NULL);
	pthread_join(thread_listenRemote, NULL);


	return 0;
}
