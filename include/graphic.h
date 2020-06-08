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