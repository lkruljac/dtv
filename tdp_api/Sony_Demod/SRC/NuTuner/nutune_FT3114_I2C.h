#ifndef __NUTUNE_FT3114_I2C_H
#define __NUTUNE_FT3114_I2C_H


/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/
#include "crules.h"
#include <stdio.h>


/******************************************************************************
**
**  Name: NuTune_I2C_Write
**
**  Description:    I2C write operations
**
**  Parameters:    	
**					DeviceAddr	- NuTune Device address
**					pArray		- Write data array pointer
**					count		- total number of array
**
**  Returns:        0 if success
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   12-16-2007   khuang initial release.
**
******************************************************************************/
uint32_t NuTune_I2C_Write(uint8_t DeviceAddr, uint8_t* pArray, uint32_t count);

/******************************************************************************
**
**  Name: NuTune_I2C_Write
**
**  Description:    I2C write operations
**
**  Parameters:    	
**					DeviceAddr	- NuTune Device address
**					pArray		- Write data array pointer
**					count		- total number of array
**
**  Returns:        0 if success
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   12-16-2007   khuang initial release.
**
******************************************************************************/
uint32_t NuTune_I2C_WriteGW(uint8_t DeviceAddr, uint8_t GatewayAddr, uint8_t TunerAddr, uint8_t* pArray, uint32_t count);


/******************************************************************************
**
**  Name: NuTune_I2C_Read
**
**  Description:    I2C read operations
**
**  Parameters:    	
**					DeviceAddr	- NuTune Device address
**					Addr		- register address for read
**					*Data		- data return
**
**  Returns:        0 if success
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   12-16-2007   khuang initial release.
**
******************************************************************************/
uint32_t NuTune_I2C_Read(uint8_t DeviceAddr, uint8_t Addr, uint8_t* mData);

/******************************************************************************
**
**  Name: NuTune_I2C_ReadGW
**
**  Description:    I2C read operations
**
**  Parameters:    	
**					DeviceAddr	- NuTune Device address
**					Addr			- register address for read
**					*Data		- data return
**
**  Returns:        0 if success
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   12-16-2007   khuang initial release.
**
******************************************************************************/


uint32_t NuTune_I2C_ReadGW(uint8_t DeviceAddr, uint8_t GatewayAddr, uint8_t TunerAddr , uint8_t RegAddr, uint8_t* mData, uint32_t count);


/******************************************************************************
**
**  Name: NuTune_Delay
**
**  Description:    Delay function in milli-second
**
**  Parameters:    	
**					mSec		- milli-second to delay
**
**  Returns:        0
**
**  Revision History:
**
**   SCR      Date      Author  Description
**  -------------------------------------------------------------------------
**   N/A   12-16-2007   khuang initial release.
**
******************************************************************************/
void NuTune_Delay(uint32_t mSec);

# endif //__NuTune_USER_DEFINE_H
