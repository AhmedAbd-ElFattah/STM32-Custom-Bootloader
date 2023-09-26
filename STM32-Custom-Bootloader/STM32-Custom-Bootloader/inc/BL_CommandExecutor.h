/*
 * File Name --> BL_CommandExecutor.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Bootloader
 * Brief	 --> Provides API for Command executor functions.
 * */
#ifndef BOOTLOADER_BL_COMMANDEXECUTOR_H_
#define BOOTLOADER_BL_COMMANDEXECUTOR_H_

#include "LIB/STD_TYPES.h"
#include "BL_Config.h"
#include "HMCAL/FMI/FMI.h"
#include "common.h"

BL_Exec_St BL_Exec_No_Cmd(void);
BL_Exec_St BL_Exec_Connect_To_BL(void);
BL_Exec_St BL_Exec_Connect_To_App(void);
BL_Exec_St BL_Exec_Update_Version(u32 Arg_MajorVersion_u32, u32 Arg_MinorVersion_u32);
BL_Exec_St BL_Exec_SET_VALID_IMAGE(void);
BL_Exec_St BL_Exec_Erase_App_IMAGE(void);
BL_Exec_St BL_Exec_Erase_Sectors(u32 Arg_Sectors_u32);
BL_Exec_St BL_Exec_Erase_Range_Of_Sectors(u32 Arg_FromSector_u32, u32 Arg_ToSector_u32);
BL_Exec_St BL_Jump_To_App(void);
BL_Exec_St BL_Exec_WRITE_32BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32);
BL_Exec_St BL_Exec_WRITE_16BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32);
BL_Exec_St BL_Exec_WRITE_8BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32);
BL_Exec_St BL_Exec_Read_32BIT_DATA_AT(u32 Arg_Address_u32, u32 *Arg_Data_pu32);
BL_Exec_St BL_Exec_Read_16BIT_DATA_AT(u32 Arg_Address_u32, u32 *Arg_Data_pu32);
BL_Exec_St BL_Exec_Read_8BIT_DATA_AT(u32 Arg_Address_u32, u32 *Arg_Data_pu32);

BL_Exec_St BL_Exec_Update_Flag(void);
void BL_Init_v(void);
void BL_Pooling_v(void);

#endif /* BOOTLOADER_BL_COMMANDEXECUTOR_H_ */
