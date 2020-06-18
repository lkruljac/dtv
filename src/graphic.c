/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* graphic.c
*
* Purpose: Enabling drawing graphic independed of rest program flow
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

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

	fontInterface = NULL;	
	/* specify the height of the font by raising the appropriate flag and setting the height value */
	fontDesc.flags = DFDESC_HEIGHT;
	fontDesc.height = 48;
	
	/* create the font and set the created font for primary surface text drawing */
	DFBCHECK(dfbInterface->CreateFont(dfbInterface, "/home/galois/fonts/DejaVuSans.ttf", &fontDesc, &fontInterface));
	DFBCHECK(primary->SetFont(primary, fontInterface));
	

	printf("Drawing logo\n");
	DrawLogo();						
	sleep(1);
	clearScreen();

	while(1){
		if(drawVolumeFlag){
			DrawVolumeStatus();
			drawVolumeFlag = 0;
		}
		if(drawCurrentChanellFlag){
			DrawChanell();
			drawCurrentChanellFlag = 0;
		}
		if(drawForbidenContentFlag){
			drawForbidenContentFlag = 0;
			DrawForbidenContent();
		}

	}


}

void DrawLogo(){
	
	/* draw image from file */
    
	IDirectFBImageProvider *provider;
	IDirectFBSurface *logoSurface = NULL;
	int32_t logoHeight, logoWidth;
	
    /* create the image provider for the specified file */
	DFBCHECK(dfbInterface->CreateImageProvider(dfbInterface, "TV-logo-app.png", &provider));
    /* get surface descriptor for the surface where the image will be rendered */
	DFBCHECK(provider->GetSurfaceDescription(provider, &surfaceDesc));
    /* create the surface for the image */
	DFBCHECK(dfbInterface->CreateSurface(dfbInterface, &surfaceDesc, &logoSurface));
    /* render the image to the surface */
	DFBCHECK(provider->RenderTo(provider, logoSurface, NULL));
	
    /* cleanup the provider after rendering the image to the surface */
	provider->Release(provider);
	
    /* fetch the logo size and add (blit) it to the screen */
	DFBCHECK(logoSurface->GetSize(logoSurface, &logoWidth, &logoHeight));
	DFBCHECK(primary->Blit(primary,
                           /*source surface*/ logoSurface,
                           /*source region, NULL to blit the whole surface*/ NULL,
                           /*destination x coordinate of the upper left corner of the image*/(screenWidth/2)-(logoWidth/2),
                           /*destination y coordinate of the upper left corner of the image*/(screenHeight/2) - (logoHeight/2)));
    
    
    /* switch between the displayed and the work buffer (update the display) */
	DFBCHECK(primary->Flip(primary,
                           /*region to be updated, NULL for the whole surface*/NULL,
                           /*flip flags*/0));
    
    /* wait 5 seconds before terminating*/
	sleep(2);


}

void DrawVolumeStatus(){

	clearScreen();


	IDirectFBImageProvider *provider;
	IDirectFBSurface *logoSurface = NULL;
	int32_t logoHeight, logoWidth;
	
    /* create the image provider for the specified file */
	DFBCHECK(dfbInterface->CreateImageProvider(dfbInterface, "speaker.png", &provider));
    /* get surface descriptor for the surface where the image will be rendered */
	DFBCHECK(provider->GetSurfaceDescription(provider, &surfaceDesc));
    /* create the surface for the image */
	DFBCHECK(dfbInterface->CreateSurface(dfbInterface, &surfaceDesc, &logoSurface));
    /* render the image to the surface */
	DFBCHECK(provider->RenderTo(provider, logoSurface, NULL));
	
    /* cleanup the provider after rendering the image to the surface */
	provider->Release(provider);
	
    /* fetch the logo size and add (blit) it to the screen */
	DFBCHECK(logoSurface->GetSize(logoSurface, &logoWidth, &logoHeight));
	DFBCHECK(primary->Blit(primary,
                           /*source surface*/ logoSurface,
                           /*source region, NULL to blit the whole surface*/ NULL,
                           /*destination x coordinate of the upper left corner of the image*/(screenWidth/2)-(logoWidth/2),
                           /*destination y coordinate of the upper left corner of the image*/(screenHeight/2) - (logoHeight/2)));



	char volumeString[25];

	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
							/*red*/ 0xFF,
							/*green*/ 0xFF,
							/*blue*/ 0xFF,
							/*alpha*/ 0xFF));			

	DFBCHECK(primary->FillRectangle(/*surface to draw on*/ primary,
									/*upper left x coordinate*/ (screenWidth/2) - 110,
									/*upper left y coordinate*/ (screenHeight/2) - 25,
									/*rectangle width*/ 115,
									/*rectangle height*/ 50));
	
	
	
	sprintf(volumeString, "%d%%", volumeStatus.volume);
	/* draw the text */
	
	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
								/*red*/ 0x25,
								/*green*/ 0x2B,
								/*blue*/ 0x87,
								/*alpha*/ 0xff));			

	DFBCHECK(primary->DrawString(primary,
									/*text to be drawn*/ volumeString,
									/*number of bytes in the string, -1 for NULL terminated strings*/ -1,
									/*x coordinate of the lower left corner of the resulting text*/ (screenWidth/2) - 107,
									/*y coordinate of the lower left corner of the resulting text*/ (screenHeight/2) + 15,
									/*in case of multiple lines, allign text to left*/ DSTF_LEFT));

	
	/* switch between the displayed and the work buffer (update the display) */
	DFBCHECK(primary->Flip(primary,
							/*region to be updated, NULL for the whole surface*/NULL,
							/*flip flags*/0));

	
    
    /* wait 5 seconds before terminating*/
	sleep(2);

	clearScreen();

}

void clearScreen()
{
	/* clear the screen before drawing anything (draw black full screen rectangle)*/
	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
								/*red*/ 0x00,
								/*green*/ 0x00,
								/*blue*/ 0x00,
								/*alpha*/ 0x00));

	DFBCHECK(primary->FillRectangle(/*surface to draw on*/ primary,
									/*upper left x coordinate*/ 0,
									/*upper left y coordinate*/ 0,
									/*rectangle width*/ screenWidth,
									/*rectangle height*/ screenHeight));
	/* draw text */
	/* switch between the displayed and the work buffer (update the display) */
	DFBCHECK(primary->Flip(primary,
							/*region to be updated, NULL for the whole surface*/NULL,
							/*flip flags*/0));




}


void DrawChanell(){
	
	clearScreen();

	char String[25];

	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
							/*red*/ 0xFF,
							/*green*/ 0xFF,
							/*blue*/ 0xFF,
							/*alpha*/ 0xFF));			

	DFBCHECK(primary->FillRectangle(/*surface to draw on*/ primary,
									/*upper left x coordinate*/ 10,
									/*upper left y coordinate*/ 20,
									/*rectangle width*/ 40,
									/*rectangle height*/ 50));
	
	
	
	sprintf(String, "%d", chanelStatus.currentProgram);
	/* draw the text */
	
	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
								/*red*/ 0x25,
								/*green*/ 0x2B,
								/*blue*/ 0x87,
								/*alpha*/ 0xff));			

	DFBCHECK(primary->DrawString(primary,
									/*text to be drawn*/ String,
									/*number of bytes in the string, -1 for NULL terminated strings*/ -1,
									/*x coordinate of the lower left corner of the resulting text*/ 15,
									/*y coordinate of the lower left corner of the resulting text*/ 65,
									/*in case of multiple lines, allign text to left*/ DSTF_LEFT));

	
	/* switch between the displayed and the work buffer (update the display) */
	DFBCHECK(primary->Flip(primary,
							/*region to be updated, NULL for the whole surface*/NULL,
							/*flip flags*/0));

	
    
    /* wait 5 seconds before terminating*/
	sleep(5);

	clearScreen();


}

void DrawForbidenContent(){
	clearScreen();

	char String[35];

	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
							/*red*/ 0xFF,
							/*green*/ 0xFF,
							/*blue*/ 0xFF,
							/*alpha*/ 0xFF));			

	DFBCHECK(primary->FillRectangle(/*surface to draw on*/ primary,
									/*upper left x coordinate*/ 0,
									/*upper left y coordinate*/ 0,
									/*rectangle width*/ screenWidth,
									/*rectangle height*/ screenHeight));
	
	
	
	sprintf(String, "Forbiden content, please insert password!", chanelStatus.currentProgram);
	/* draw the text */
	
	DFBCHECK(primary->SetColor(/*surface to draw on*/ primary,
								/*red*/ 0x25,
								/*green*/ 0x2B,
								/*blue*/ 0x87,
								/*alpha*/ 0xff));			

	DFBCHECK(primary->DrawString(primary,
									/*text to be drawn*/ String,
									/*number of bytes in the string, -1 for NULL terminated strings*/ -1,
									/*x coordinate of the lower left corner of the resulting text*/ 15,
									/*y coordinate of the lower left corner of the resulting text*/ 65,
									/*in case of multiple lines, allign text to left*/ DSTF_LEFT));

	
	/* switch between the displayed and the work buffer (update the display) */
	DFBCHECK(primary->Flip(primary,
							/*region to be updated, NULL for the whole surface*/NULL,
							/*flip flags*/0));

	
    
    /* wait 5 seconds before terminating*/
	sleep(5);

	clearScreen();
}