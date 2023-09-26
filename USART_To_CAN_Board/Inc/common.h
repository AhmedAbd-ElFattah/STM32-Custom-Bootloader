#ifndef COMMON_H
#define COMMON_H
/*
 * File Name --> common.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Contain common structure of send/receive data of serial communication and
 *               order of shown elements in gui
 * Note      --> This file is common between GUI & Microcontroller.It's portable file between C & C++.
 * */

#ifdef __cplusplus
#include <QtGlobal>
#include <array>
#include "ApplicationConfigurations.h"

#else
#include "LIB/STD_TYPES.h"
#endif

/*
==================================================
  Start Section --> Common configurations
==================================================
 */


/*
==================================================
  End Section --> Common configurations
==================================================
 */

/*
==================================================
  Start Section --> Common datatypes
==================================================
 */
/*Note For portability of file,
 * any primitive datatype used in this file must use these only*/

#ifdef __cplusplus

#define COMMON_u8   quint8
#define COMMON_u16  quint16
#define COMMON_u32  quint32
#define COMMON_u64  quint64

#define COMMON_s8   qint8
#define COMMON_s16  qint16
#define COMMON_s32  qint32
#define COMMON_s64  qint64

#else

#define COMMON_u8   u8
#define COMMON_u16  u16
#define COMMON_u32  u32
#define COMMON_u64  u64

#define COMMON_s8   s8
#define COMMON_s16  s16
#define COMMON_s32  s32
#define COMMON_s64  s64

#endif

/*
==================================================
  End Section --> Common datatypes
==================================================
 */

/*
==================================================
  Start Section --> Communication structure
==================================================
 */
#define APP_CONFIG_BUFFER_SIZE 4

union UITxSerialDataFrame {
	struct {
		COMMON_u32   Command;
		COMMON_u32   Flags;
		COMMON_u32   Parameter1;
		COMMON_u32   Parameter2;
	};
	/*HOST_CMD_UPDATE_VERSION*/
	struct {
		COMMON_u32   Version_Command;
		COMMON_u32   Version_Flags;
		COMMON_u32   Version_MajorVersion;
		COMMON_u32   Version_MinorVersion;
	};
	/*HOST_CMD_ERASE_SECTORS or HOST_CMD_ERASE_RANGE_OF_SECTORS*/
	struct {
		COMMON_u32   EraseSectors_Command;
		COMMON_u32   EraseSectors_Sectors;
		COMMON_u32   EraseSectors_FromSector;
		COMMON_u32   EraseSectors_ToSector;
	};
	/*HOST_CMD_WRITE_32BIT_DATA_AT or HOST_CMD_WRITE_16BIT_DATA_AT or HOST_CMD_WRITE_8BIT_DATA_AT*/
	struct {
		COMMON_u32   Write_Command;
		COMMON_u32   Write_Reserved;
		COMMON_u32   Write_Address;
		COMMON_u32   Write_Value;
	};


#ifdef __cplusplus
	std::array<COMMON_u32, APP_CONFIG_BUFFER_SIZE> Buffer;
#else
	COMMON_u32 Buffer [APP_CONFIG_BUFFER_SIZE];
	COMMON_u8  Buffer_u8 [4*APP_CONFIG_BUFFER_SIZE];
#endif
}UITxSerialDataFrame;

typedef enum{
    HOST_CMD_NO_CMD, /*No Params*/
    HOST_CMD_ConnectToBL, /*No Params*/
    HOST_CMD_ConnectToApp, /*No Params*/
    HOST_CMD_SET_UPDATE_FLAG,                  /*No Params*/
    HOST_CMD_UPDATE_VERSION,              /*Param 1 Major Version ( 1byte ), Param 2 Minor Version ( 1byte )*/
    HOST_CMD_SET_VALID_IMAGE,                /*No Params*/

    HOST_CMD_ERASE_APP_IMAGE,              /*No Params*/
    HOST_CMD_ERASE_SECTORS,               /*setted bits in param1 is the selected sectors*/
    HOST_CMD_ERASE_RANGE_OF_SECTORS,     /*param 1 from sector param 2 to sector*/

    HOST_CMD_JumpToApp,/*No Params*/

    HOST_CMD_WRITE_32BIT_DATA_AT,          /*param 1 Address param 2 Data*/
    HOST_CMD_WRITE_16BIT_DATA_AT,          /*param 1 Address param 2 Data*/
    HOST_CMD_WRITE_8BIT_DATA_AT,          /*param 1 Address param 2 Data*/

    HOST_CMD_Read_32BIT_DATA_AT,          /*param 1 Address*/
    HOST_CMD_Read_16BIT_DATA_AT,          /*param 1 Address*/
    HOST_CMD_Read_8BIT_DATA_AT,          /*param 1 Address*/
}HostCMDs;



/*
==================================================
  End Section --> Communication structure
==================================================
 */
#endif // COMMON_H
