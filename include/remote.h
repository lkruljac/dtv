/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* remote.h
*
* Purpose: Enabling using remote independed of rest program flow
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

#ifndef REMOTE_H
#define REMOTE_H

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <pthread.h>

#include "globals.h"
#include "streamplayer.h"

int32_t inputFileDesc;

void *listenRemote();
int32_t getKeys(int32_t count, uint8_t* buf, int32_t* eventsRead);



#endif