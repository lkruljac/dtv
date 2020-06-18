/****************************************************************************
*
* FERIT
*
* -----------------------------------------------------
* Konstrukcijski zadatak kolegij: Digitalna videotehnika
* -----------------------------------------------------
*
* graphic.h
*
* Purpose: Enabling drawing graphic independed of rest program flow
*
* Made on 18.6.2020.
*
* @Author Luka Kruljac
* @E-mail luka97kruljac@gmail.com
*****************************************************************************/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#define DFBCHECK(x...)                                      \
{                                                           \
DFBResult err = x;                                          \
                                                            \
if (err != DFB_OK)                                          \
  {                                                         \
    fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ );  \
    DirectFBErrorFatal( #x, err );                          \
  }                                                         \
}




void *GraphicThread();
void DrawLogo();
void DrawVolumeStatus();
void DrawChanell();
void clearScreen();
void DrawForbidenContent();


#endif