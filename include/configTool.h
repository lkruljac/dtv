/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* configTool.h
*
* Purpose: Parsing .cfg files, filling global structure variable and printing results
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

// Functions for parsing config file to config struct

#ifndef CONFIGTOOL_H
#define CONFIGTOOL_H

#include<stdio.h>
#include<stdlib.h>
#include"globals.h"

int loadConfigFile(char *configFileName);

#endif