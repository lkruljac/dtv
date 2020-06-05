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


#endif