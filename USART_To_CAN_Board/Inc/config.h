/*
 * File Name --> config.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Application
 * Brief	 --> Configurations of USART to CAN board.
 * */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "HMCAL/DMA/DMA.h"


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

#define CONFIG_CAN_FILTER_ID				1


/*
==================================================
  End Section  --> CAN Configurations
==================================================
 */



#endif /* CONFIG_H_ */
