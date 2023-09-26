/*
 * File Name --> CANAnalyzer_Config.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Bootloader
 * Brief	 --> Bootloader configurations
 * */

#ifndef BOOTLOADER_BL_CONFIG_H_
#define BOOTLOADER_BL_CONFIG_H_

#include "HMCAL/DMA/DMA.h"
/*
==================================================
  Start Section --> Bootloader Selection
==================================================
 */
#define CAN_BOOTLOADER		1
#define USART_BOOTLOADER	2

#define BOOTLOADER_TYPE		CAN_BOOTLOADER

#if ((BOOTLOADER_TYPE != USART_BOOTLOADER) && (BOOTLOADER_TYPE != CAN_BOOTLOADER))

#error "Please select available bootloader type"

#endif
/*
==================================================
  Start Section --> Bootloader Selection
==================================================
 */

/*
==================================================
  Start Section --> Flash sections
==================================================
 */

#define BL_SECTORS_NUM					8

#define BL_CFG_SECTOR_0_ADDRESS_START	0x08000000
#define BL_CFG_SECTOR_0_ADDRESS_END		0x08003FFF

#define BL_CFG_SECTOR_1_ADDRESS_START	0x08004000
#define BL_CFG_SECTOR_1_ADDRESS_END		0x08007FFF

#define BL_CFG_SECTOR_2_ADDRESS_START	0x08008000
#define BL_CFG_SECTOR_2_ADDRESS_END		0x0800BFFF

#define BL_CFG_SECTOR_3_ADDRESS_START	0x0800C000
#define BL_CFG_SECTOR_3_ADDRESS_END		0x0800FFFF

#define BL_CFG_SECTOR_4_ADDRESS_START	0x08010000
#define BL_CFG_SECTOR_4_ADDRESS_END		0x0801FFFF

#define BL_CFG_SECTOR_5_ADDRESS_START	0x08020000
#define BL_CFG_SECTOR_5_ADDRESS_END		0x0803FFFF


#define BL_CFG_SECTOR_6_ADDRESS_START	0x08040000
#define BL_CFG_SECTOR_6_ADDRESS_END		0x0805FFFF

#define BL_CFG_SECTOR_7_ADDRESS_START	0x08060000
#define BL_CFG_SECTOR_7_ADDRESS_END		0x0807FFFF

/*
==================================================
  End Section --> Flash sections
==================================================
 */

/*
==================================================
  Start Section --> DMA Configurations
==================================================
 */
#define CONFIG_DMA_INSTANCE_ID					1
#define CONFIG_DMA_STREAM_NUMBER				5
#define CONFIG_DMA_CHANNEL_STREAM				DMA1_USART2_RX_CH_4_S_5
/*
==================================================
  End Section --> DMA Configurations
==================================================
 */

/*
==================================================
  Start Section --> USART Configurations
==================================================
 */
#define CONFIG_USART_COMMUNICATION_BAUDRATE		115200
#define CONFIG_USART_GPIO						'A'
#define CONFIG_USART_INSTANCE_ID				2
#define CONFIG_USART_TRANSMIT_PIN				2
#define CONFIG_USART_RECEIVE_PIN				3
/*
==================================================
  End Section -->  USART Configurations
==================================================
 */

/*
==================================================
  Start Section --> CAN Configurations
==================================================
 */
#define CONFIG_CAN_DEVICE_ID		16

#define CONFIG_CAN_ECHO_MESSAGE_ID	66
#define CONFIG_CAN_INSTANCE_ID		1
#define CONFIG_CAN_GPIO_ID			'B'
#define CONFIG_CAN_RxPIN			8
#define CONFIG_CAN_TxPIN			9
/*Baudrate configurations*/
#define CONFIG_CAN_BAUDRATE_PRESCALLER		1
#define CONFIG_CAN_TIME_SEGMENT_1			13
#define CONFIG_CAN_TIME_SEGMENT_2			2
#define CONFIG_CAN_RESYNCHRONIZATION_JUMP	1

/*Receive Filter Configurations*/

#define CONFIG_CAN_FILTER_ID				0
#define CONFIG_CAN_FILTER_MESSAGE_ID		0x1F
#define CONFIG_CAN_FILTER_MESSAGE_MASK		0xFFFFFFE0

/*
==================================================
  End Section  --> CAN Configurations
==================================================
 */

/*
==================================================
  Start Section  --> CAN Bootloader Configurations
==================================================
 */
#define CONFIG_BL_CAN_TIME_TO_WAIT_UPDATE_IN_SECONDS	10
/*
==================================================
  End Section  	 --> CAN Bootloader Configurations
==================================================
 */
/*
==================================================
  Start Section --> App Flash section Configurations
==================================================
 */
/*Address that contain update flag*/
#define UPDATE_FLAG_ADDRESS 			((u32)0x807FFFC)

#define BL_APP_START_SECTION_NUM		2
#define BL_APP_ADDRESS					BL_CFG_SECTOR_2_ADDRESS_START
/*
==================================================
  End Section --> App Flash section Configurations
==================================================
 */


/*
==================================================
  Start Section --> Bootloader data addresses locations
==================================================
 */
#define VALID_IMAGE_FLAG_ADDRESS 		(u32)0x807fff8
#define BL_VERSION_ADDRESS				(BL_CFG_SECTOR_7_ADDRESS_END-3)
#define BL_VALID_IMAGE_ADDRESS			(BL_VERSION_ADDRESS-4)
#define BL_UPDATE_FLAG_ADDRESS			(BL_VALID_IMAGE_ADDRESS-4)

#define UPDATE_FLAG_VALUE				0x5A5A5A5A
#define VALID_IMAGE_FLAG_VALUE			0x5A5A5A5A
/*
==================================================
  End Section --> Bootloader data addresses locations
==================================================
 */

#endif /* BOOTLOADER_BL_CONFIG_H_ */
