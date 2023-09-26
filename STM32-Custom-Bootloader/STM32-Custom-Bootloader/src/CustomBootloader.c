/*
==================================================
  Start Section --> File includes
==================================================
 */

#include "LMCAL/SCB/SCB.h"

#include "LIB/Delay/Delay.h"

#include "LIB/utils.h"

#include "BL_Config.h"
#include "common.h"
#include "BL_CommandExecutor.h"

#if BOOTLOADER_TYPE == USART_BOOTLOADER

#include "HMCAL/USART/USART.h"
#include "HMCAL/Interrupt/InterruptHandlers.h"
#include "HMCAL/DMA/DMA.h"

#elif BOOTLOADER_TYPE == CAN_BOOTLOADER

#include "HMCAL/CAN/CAN.h"

#else

#error "Please select available bootloader type"

#endif

/*
==================================================
  End Section --> File includes
==================================================
 */

#if BOOTLOADER_TYPE == USART_BOOTLOADER

static USART_Cfg GS_BLUSART_USART_Cfg;

#elif BOOTLOADER_TYPE == CAN_BOOTLOADER

static CAN_Cfg G_Communication_CAN_Cfg;
static CAN_TxData G_TransmitMessage_CAN_TxData;
static CAN_RxData G_ReceiveMessage_CAN_RxData;

#else

#error "Please select available bootloader type"

#endif

static void ExecuteCommand(void);

union UITxSerialDataFrame UITxSerialDataFrame;

/*
==================================================
  Start Section --> Implementation of each command's function
==================================================
 */

BL_Exec_St BL_Exec_No_Cmd(void){

	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Connect_To_BL(void){

	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Update_Flag(void){
	FMI_FlashWriteU32Data_v(UPDATE_FLAG_ADDRESS, UPDATE_FLAG_VALUE);
	SCB_SWReset();
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Connect_To_App(void){

	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Update_Version(u32 Arg_MajorVersion_u32, u32 Arg_MinorVersion_u32){

	return BL_CMD_EXEC_SUCCEED_STATUS;
}


BL_Exec_St BL_Exec_SET_VALID_IMAGE(void){


	FMI_FlashWriteU32Data_v(VALID_IMAGE_FLAG_ADDRESS, VALID_IMAGE_FLAG_VALUE);

	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Erase_App_IMAGE(void){
	for (u8 L_i_u8 = BL_APP_START_SECTION_NUM; L_i_u8 < BL_SECTORS_NUM;L_i_u8++){
		FMI_EraseFlashSector_v(L_i_u8);
	}

	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Erase_Sectors(u32 Arg_Sectors_u32){
	/*Each sector represented by a bit in Arg_Sectors_u32
	 * High bit indicates that this sector needed to be erased*/
	for (u8 L_i_u8=0; L_i_u8<31 ; L_i_u8++){
		if (GET_BIT(Arg_Sectors_u32, L_i_u8)){
			FMI_EraseFlashSector_v(L_i_u8);
		}
	}
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_Erase_Range_Of_Sectors(u32 Arg_FromSector_u32, u32 Arg_ToSector_u32){

	for (u8 L_i_u8 = Arg_FromSector_u32; L_i_u8 <= Arg_ToSector_u32;L_i_u8++){
		FMI_EraseFlashSector_v(L_i_u8);
	}
	return BL_CMD_EXEC_SUCCEED_STATUS;
}



BL_Exec_St BL_Jump_To_App(void){
	typedef void (*APP_CALL) (void);
	APP_CALL App_To_Call = *(APP_CALL *)( (u32)BL_APP_ADDRESS +4);
	SCB_SetVectorTableOffset_void(BL_APP_ADDRESS, SCB_VectorTableInFlash);
	App_To_Call();
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_WRITE_32BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32){
	FMI_FlashWriteU32Data_v(Arg_Address_u32, Arg_Data_u32);
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_WRITE_16BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32){
	FMI_FlashWriteU16Data_v(Arg_Address_u32, Arg_Data_u32);
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

BL_Exec_St BL_Exec_WRITE_8BIT_DATA_AT(u32 Arg_Address_u32, u32 Arg_Data_u32){
	FMI_FlashWriteU8Data_v(Arg_Address_u32, Arg_Data_u32);
	return BL_CMD_EXEC_SUCCEED_STATUS;
}

/*
==================================================
  End Section --> Implementation of each command's function
==================================================
 */

void BL_Pooling_v(){
#if BOOTLOADER_TYPE == USART_BOOTLOADER
	if (UITxSerialDataFrame.Command == HOST_CMD_JumpToApp){
		SCB_SWReset();
	}
#elif BOOTLOADER_TYPE == CAN_BOOTLOADER
	if ((VALID_IMAGE_FLAG_VALUE != UTILS_READ_ADDRESS(VALID_IMAGE_FLAG_ADDRESS))){
		CAN_Receive_v(&G_Communication_CAN_Cfg, &G_ReceiveMessage_CAN_RxData, STD_MAX_DELAY, NULL);
	}
	else{
		u32 L_TimeOutErr_u32;
		/*wait for x second*/
		CAN_Receive_v(&G_Communication_CAN_Cfg, &G_ReceiveMessage_CAN_RxData, 1000*CONFIG_BL_CAN_TIME_TO_WAIT_UPDATE_IN_SECONDS, &L_TimeOutErr_u32);
		if (STD_TimeOutError == L_TimeOutErr_u32){
			return ;
		}
	}

	UITxSerialDataFrame.Command = G_ReceiveMessage_CAN_RxData.ID - CONFIG_CAN_DEVICE_ID;
	if (HOST_CMD_JumpToApp == UITxSerialDataFrame.Command){
		SCB_SWReset();
	}
	for (u8 L_i_u8 = 0; L_i_u8< G_ReceiveMessage_CAN_RxData.DataLength; ++L_i_u8){
		UITxSerialDataFrame.Buffer_u8[8+L_i_u8] = G_ReceiveMessage_CAN_RxData.ReceivedData[L_i_u8];
	}
	ExecuteCommand();


#endif
}

void BL_Init_v(void){

#if BOOTLOADER_TYPE == USART_BOOTLOADER
	/*Configure USART*/

	GS_BLUSART_USART_Cfg.BaudRate = CONFIG_USART_COMMUNICATION_BAUDRATE;
	GS_BLUSART_USART_Cfg.GPIOInstanceId = CONFIG_USART_GPIO;
	GS_BLUSART_USART_Cfg.GPIOPins = (1<<CONFIG_USART_TRANSMIT_PIN)|(1<<CONFIG_USART_RECEIVE_PIN);
	GS_BLUSART_USART_Cfg.InstanceId = CONFIG_USART_INSTANCE_ID;
	GS_BLUSART_USART_Cfg.TransferDirection = USART_TRANSMIT | USART_RECEIVE;
	GS_BLUSART_USART_Cfg.DMA = USART_DMA_RECEIVE;
	USART_Config_v(&GS_BLUSART_USART_Cfg);

	/*Configure DMA*/
	DMA_Cfg L_DMA_Configurations = {0};

	L_DMA_Configurations.CircularMode = DMA_CIRCULAR_MODE_ENABLE;
	L_DMA_Configurations.DataSize = DMA_DATA_SIZE_MEM_WORD_PERPH_BYTE;
	L_DMA_Configurations.IncrementMode = DMA_INCREMENT_MODE_INCR_MEM_FIXED_PERPH;
	L_DMA_Configurations.InstanceId = CONFIG_DMA_INSTANCE_ID;

	L_DMA_Configurations.Interrupt = DMA_INTERRUPT_TRANSFER_COMPLETE;
	L_DMA_Configurations.MemoryAddress = (u32)&UITxSerialDataFrame.Buffer;
	L_DMA_Configurations.PeripheralAddress = USART_GetAdressForDMA_u32(&GS_BLUSART_USART_Cfg);
	L_DMA_Configurations.Size = 4*ARRAY_LENGTH(UITxSerialDataFrame.Buffer);
	L_DMA_Configurations.TransferDir = DMA_TRANSFER_DIR_PERPH_TO_MEM;
	DMA_Config_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);
	InterruptHandler_SetDMACallback_v(CONFIG_DMA_INSTANCE_ID, CONFIG_DMA_STREAM_NUMBER, DMA_INTERRUPT_TRANSFER_COMPLETE, ExecuteCommand);

	DMA_EnableDMA_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);
	USART_EnableUSART_v(&GS_BLUSART_USART_Cfg);

#elif BOOTLOADER_TYPE == CAN_BOOTLOADER
	G_Communication_CAN_Cfg.TimeTriggeredEn = STD_DIASBLE;
	G_Communication_CAN_Cfg.AutoBusOffEn = STD_DIASBLE;
	G_Communication_CAN_Cfg.AutoWakeUpEn = STD_DIASBLE;
	G_Communication_CAN_Cfg.AutoReTransmissionEn = STD_ENABLE;
	G_Communication_CAN_Cfg.ReceiveFifoLockOnOverrunEn = STD_DIASBLE;
	G_Communication_CAN_Cfg.TransmitFifoPriority = CAN_TRANSMIT_FIFO_PRIORITY_BY_MSG_ID;
	G_Communication_CAN_Cfg.OperatingMode = CAN_OPERATING_MODE_NORMAL;
	G_Communication_CAN_Cfg.GPIOInstanceId = CONFIG_CAN_GPIO_ID;
	G_Communication_CAN_Cfg.GPIOPins = (1<<CONFIG_CAN_RxPIN) | (1<<CONFIG_CAN_TxPIN);
	G_Communication_CAN_Cfg.InstanceId = CONFIG_CAN_INSTANCE_ID;
	G_Communication_CAN_Cfg.BaudRatePrescaller = CONFIG_CAN_BAUDRATE_PRESCALLER;
	G_Communication_CAN_Cfg.TimeSegment_1 = CONFIG_CAN_TIME_SEGMENT_1;
	G_Communication_CAN_Cfg.TimeSegment_2 = CONFIG_CAN_TIME_SEGMENT_2;
	G_Communication_CAN_Cfg.ResychronizationJump = CONFIG_CAN_RESYNCHRONIZATION_JUMP;

	CAN_Config_v(&G_Communication_CAN_Cfg);

	/*Configure Receive Filter*/
	CAN_FilterConfig L_RxFilter_CAN_FilterConfig = {0};
	L_RxFilter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_1ID32_1MASK32;
	L_RxFilter_CAN_FilterConfig.FilterId = CONFIG_CAN_FILTER_ID;
	L_RxFilter_CAN_FilterConfig.ID1 = CONFIG_CAN_FILTER_MESSAGE_ID;
	L_RxFilter_CAN_FilterConfig.Mask1 = CONFIG_CAN_FILTER_MESSAGE_MASK;
	L_RxFilter_CAN_FilterConfig.FIFONumber = CAN_FILTER_FIFONUMBER_1;
	L_RxFilter_CAN_FilterConfig.IdType = CAN_Standard_Id;
	L_RxFilter_CAN_FilterConfig.FrameType = CAN_Data_Frame;
	CAN_AddRxFilter_v(&G_Communication_CAN_Cfg, &L_RxFilter_CAN_FilterConfig);
#else
#error "Please select available bootloader type"
#endif
}

void ExecuteCommand(void){

	BL_Exec_St L_Status_BL_Exec_St;
	u32 L_ReturnValue_u32 = -1;

	switch(UITxSerialDataFrame.Command){
	case HOST_CMD_NO_CMD:
		L_Status_BL_Exec_St = BL_Exec_No_Cmd();
		break;

	case HOST_CMD_ConnectToBL:
		L_Status_BL_Exec_St = BL_Exec_Connect_To_BL();
		break;

	case HOST_CMD_ConnectToApp:
		L_Status_BL_Exec_St = BL_Exec_Connect_To_App();
		break;

	case HOST_CMD_SET_UPDATE_FLAG:
		L_Status_BL_Exec_St = BL_Exec_Update_Flag();
		break;

	case HOST_CMD_UPDATE_VERSION:
		L_Status_BL_Exec_St = BL_Exec_Update_Version(UITxSerialDataFrame.Version_MajorVersion, UITxSerialDataFrame.Version_MinorVersion);
		break;

	case HOST_CMD_SET_VALID_IMAGE:
		L_Status_BL_Exec_St = BL_Exec_SET_VALID_IMAGE();
		break;

	case HOST_CMD_ERASE_APP_IMAGE:
		L_Status_BL_Exec_St = BL_Exec_Erase_App_IMAGE();
		break;

	case HOST_CMD_ERASE_SECTORS:
		L_Status_BL_Exec_St = BL_Exec_Erase_Sectors(UITxSerialDataFrame.EraseSectors_Sectors);
		break;

	case HOST_CMD_ERASE_RANGE_OF_SECTORS:
		L_Status_BL_Exec_St = BL_Exec_Erase_Range_Of_Sectors(UITxSerialDataFrame.EraseSectors_FromSector, UITxSerialDataFrame.EraseSectors_ToSector);
		break;


	case HOST_CMD_WRITE_32BIT_DATA_AT:
		L_Status_BL_Exec_St = BL_Exec_WRITE_32BIT_DATA_AT(UITxSerialDataFrame.Write_Address, UITxSerialDataFrame.Write_Value);
		break;

	case HOST_CMD_WRITE_16BIT_DATA_AT:
		L_Status_BL_Exec_St = BL_Exec_WRITE_16BIT_DATA_AT(UITxSerialDataFrame.Write_Address, UITxSerialDataFrame.Write_Value);
		break;

	case HOST_CMD_WRITE_8BIT_DATA_AT:
		L_Status_BL_Exec_St = BL_Exec_WRITE_8BIT_DATA_AT(UITxSerialDataFrame.Write_Address, UITxSerialDataFrame.Write_Value);
		break;

	}

	u8 L_TransmitArr [] = {(u8)L_Status_BL_Exec_St, (u8)L_ReturnValue_u32};

#if BOOTLOADER_TYPE == USART_BOOTLOADER
	USART_SendU8ArrayPooling_v(
			&GS_BLUSART_USART_Cfg,
			L_TransmitArr,
			ARRAY_LENGTH(L_TransmitArr),
			STD_MAX_DELAY, NULL);


#elif BOOTLOADER_TYPE == CAN_BOOTLOADER
	G_TransmitMessage_CAN_TxData.DataLength = ARRAY_LENGTH(L_TransmitArr);
	G_TransmitMessage_CAN_TxData.DataPtr = L_TransmitArr;
	G_TransmitMessage_CAN_TxData.FrameType = CAN_Data_Frame;
	G_TransmitMessage_CAN_TxData.ID = CONFIG_CAN_ECHO_MESSAGE_ID;
	G_TransmitMessage_CAN_TxData.IdType = CAN_Standard_Id;
	CAN_SendData_v(
			&G_Communication_CAN_Cfg,
			&G_TransmitMessage_CAN_TxData,
			STD_MAX_DELAY,
			NULL);

#else

#error "Please select available bootloader type"

#endif

}

