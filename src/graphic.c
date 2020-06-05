#include "graphic.h"
#include <stdio.h>
#include <directfb.h>
#include "globals.h"
void *GraphicThread(){
	

	printf("Graphic thread started..\n");

	/* initialize DirectFB */
	DFBCHECK(DirectFBInit(NULL, NULL));
    /* fetch the DirectFB interface */
	DFBCHECK(DirectFBCreate(&dfbInterface));
    /* tell the DirectFB to take the full screen for this application */
	DFBCHECK(dfbInterface->SetCooperativeLevel(dfbInterface, DFSCL_FULLSCREEN));

	

	/* create primary surface with double buffering enabled */
	surfaceDesc.flags = DSDESC_CAPS;
	surfaceDesc.caps = DSCAPS_PRIMARY | DSCAPS_FLIPPING;
	DFBCHECK (dfbInterface->CreateSurface(dfbInterface, &surfaceDesc, &primary));

	/* fetch the screen size */
	DFBCHECK (primary->GetSize(primary, &screenWidth, &screenHeight));

	/* clear the screen before drawing anything (draw black full screen rectangle)*/
	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
								/*red*/ 0x00,
								/*green*/ 0x00,
								/*blue*/ 0x00,
								/*alpha*/ 0xff));
	DFBCHECK(primary->FillRectangle(/*surface to draw on*/ primary,
									/*upper left x coordinate*/ 0,
									/*upper left y coordinate*/ 0,
									/*rectangle width*/ screenWidth,
									/*rectangle height*/ screenHeight));

									




}