#include "HMCAL/CAN/CAN.h"
#include "LIB/Delay/Delay.h"
#include "HMCAL/USART/USART.h"
#include "common.h"
#include "config.h"
#include "LIB/utils.h"
#include "HMCAL/DMA/DMA.h"
#include "HMCAL/Interrupt/InterruptHandlers.h"

static u8 GS_TxData_u8[8];

static CAN_Cfg GS_COM_CAN_Cfg;
static CAN_TxData GS_TransmitMessage_CAN_TxData;
static CAN_RxData GS_ReceiveMessage_CAN_RxData;

static USART_Cfg GS_COM_USART_Cfg;



void SendCANFrame(void){
	u16 L_Command_u8 = (u16) UITxSerialDataFrame.Buffer[0];
	u16 L_ID_u8 = (u16) UITxSerialDataFrame.Buffer[1];

	GS_TransmitMessage_CAN_TxData.ID = L_ID_u8 + L_Command_u8;

	GS_TransmitMessage_CAN_TxData.DataPtr = (u8 *)&UITxSerialDataFrame.Buffer_u8[8];
	/*Send CAN Frame which received from UART*/
	CAN_SendData_v(&GS_COM_CAN_Cfg, &GS_TransmitMessage_CAN_TxData, STD_MAX_DELAY, NULL);
	/*Wait to receive echo.*/
	CAN_Receive_v(&GS_COM_CAN_Cfg, &GS_ReceiveMessage_CAN_RxData, STD_MAX_DELAY, NULL);
	/*Send echo to USART*/
	USART_SendU8ArrayPooling_v(
			&GS_COM_USART_Cfg,
			GS_ReceiveMessage_CAN_RxData.ReceivedData,
			GS_ReceiveMessage_CAN_RxData.DataLength,
			STD_MAX_DELAY,
			NULL);
}

int main(){
	/*Configure CAN that will send/receive message to/from USART*/
	GS_COM_CAN_Cfg.TimeTriggeredEn = STD_DIASBLE;
	GS_COM_CAN_Cfg.AutoBusOffEn = STD_DIASBLE;
	GS_COM_CAN_Cfg.AutoWakeUpEn = STD_DIASBLE;
	GS_COM_CAN_Cfg.AutoReTransmissionEn = STD_ENABLE;
	GS_COM_CAN_Cfg.ReceiveFifoLockOnOverrunEn = STD_DIASBLE;
	GS_COM_CAN_Cfg.TransmitFifoPriority = CAN_TRANSMIT_FIFO_PRIORITY_BY_MSG_ID;
	GS_COM_CAN_Cfg.OperatingMode = CAN_OPERATING_MODE_NORMAL;
	GS_COM_CAN_Cfg.GPIOInstanceId = CONFIG_CAN_GPIO_ID;
	GS_COM_CAN_Cfg.GPIOPins = (1<<CONFIG_CAN_RxPIN) | (1<<CONFIG_CAN_TxPIN);
	GS_COM_CAN_Cfg.InstanceId = CONFIG_CAN_INSTANCE_ID;

	GS_COM_CAN_Cfg.BaudRatePrescaller = CONFIG_CAN_BAUDRATE_PRESCALLER;
	GS_COM_CAN_Cfg.TimeSegment_1 = CONFIG_CAN_TIME_SEGMENT_1;
	GS_COM_CAN_Cfg.TimeSegment_2 = CONFIG_CAN_TIME_SEGMENT_2;
	GS_COM_CAN_Cfg.ResychronizationJump = CONFIG_CAN_RESYNCHRONIZATION_JUMP;

	CAN_Config_v(&GS_COM_CAN_Cfg);

	/*Configure CAN header of message that will be sent by CAN that contains received USART messages*/
	GS_TransmitMessage_CAN_TxData.DataLength = ARRAY_LENGTH(GS_TxData_u8);
	GS_TransmitMessage_CAN_TxData.FrameType = CAN_Data_Frame;
	GS_TransmitMessage_CAN_TxData.IdType = CAN_Standard_Id;
	GS_TransmitMessage_CAN_TxData.DataPtr = GS_TxData_u8;


	CAN_FilterConfig L_EchoFilter_CAN_FilterConfig = {0};
	L_EchoFilter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_4ID16;
	L_EchoFilter_CAN_FilterConfig.FilterId = CONFIG_CAN_FILTER_ID;
	L_EchoFilter_CAN_FilterConfig.ID1 = CONFIG_CAN_ECHO_MESSAGE_ID;
	L_EchoFilter_CAN_FilterConfig.FIFONumber = CAN_FILTER_FIFONUMBER_1;
	L_EchoFilter_CAN_FilterConfig.IdType = CAN_Standard_Id;
	L_EchoFilter_CAN_FilterConfig.FrameType = CAN_Data_Frame;
	CAN_AddRxFilter_v(&GS_COM_CAN_Cfg, &L_EchoFilter_CAN_FilterConfig);

	/*Configure USART*/
	GS_COM_USART_Cfg.BaudRate = CONFIG_USART_COMMUNICATION_BAUDRATE;
	GS_COM_USART_Cfg.GPIOInstanceId = CONFIG_USART_GPIO;
	GS_COM_USART_Cfg.GPIOPins = (1<<CONFIG_USART_TRANSMIT_PIN)|(1<<CONFIG_USART_RECEIVE_PIN);
	GS_COM_USART_Cfg.InstanceId = CONFIG_USART_INSTANCE_ID;
	GS_COM_USART_Cfg.TransferDirection = USART_TRANSMIT | USART_RECEIVE;
	GS_COM_USART_Cfg.DMA = USART_DMA_RECEIVE;
	USART_Config_v(&GS_COM_USART_Cfg);

	/*Configure DMA*/
	DMA_Cfg L_DMA_Configurations = {0};

	L_DMA_Configurations.CircularMode = DMA_CIRCULAR_MODE_ENABLE;
	L_DMA_Configurations.DataSize = DMA_DATA_SIZE_MEM_WORD_PERPH_BYTE;
	L_DMA_Configurations.IncrementMode = DMA_INCREMENT_MODE_INCR_MEM_FIXED_PERPH;
	L_DMA_Configurations.InstanceId = CONFIG_DMA_INSTANCE_ID;

	L_DMA_Configurations.Interrupt = DMA_INTERRUPT_TRANSFER_COMPLETE;
	L_DMA_Configurations.MemoryAddress = (u32)&UITxSerialDataFrame.Buffer;
	L_DMA_Configurations.PeripheralAddress = USART_GetAdressForDMA_u32(&GS_COM_USART_Cfg);
	L_DMA_Configurations.Size = 4*ARRAY_LENGTH(UITxSerialDataFrame.Buffer);
	L_DMA_Configurations.TransferDir = DMA_TRANSFER_DIR_PERPH_TO_MEM;
	DMA_Config_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);

	InterruptHandler_SetDMACallback_v(CONFIG_DMA_INSTANCE_ID, CONFIG_DMA_STREAM_NUMBER, DMA_INTERRUPT_TRANSFER_COMPLETE, SendCANFrame);

	DMA_EnableDMA_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);
	USART_EnableUSART_v(&GS_COM_USART_Cfg);



	while(1){


	}
}
