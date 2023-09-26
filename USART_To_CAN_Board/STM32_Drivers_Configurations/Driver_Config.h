/*
 * File Name --> Driver_Config.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Configurations
 * Brief	 --> Configurations of system clock.
 * */

#ifndef STM32_DRIVERS_CONFIGURATIONS_DRIVER_CONFIG_H_
#define STM32_DRIVERS_CONFIGURATIONS_DRIVER_CONFIG_H_




/*
==================================================
  Start Section --> File Includes
==================================================
 */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
/*
==================================================
  End   Section --> File Includes
==================================================
 */

#define CONFIG_USE_HARDWARE_FPU 			1
#define CONFIG_USE_HARDWARE_CRC 			1


#define CONFIG_TICK_TIME_IN_MilliSeconds	1

#define CONFIG_SYSTICK_USE_EXTERNAL_CLOCK	1


#define CONFIG_NO_RTOS				    1
#define CONFIG_USE_RTOS_EDURTOS		2
#define CONFIG_USE_RTOS_FREERTOS	3


#define CONFIG_USE_RTOS		CONFIG_NO_RTOS

#ifndef CONFIG_USE_RTOS
#error "You must specify wheiter you will use RTOS or not"
#endif

#if !((CONFIG_USE_RTOS==CONFIG_NO_RTOS)||(CONFIG_USE_RTOS==CONFIG_USE_RTOS_EDURTOS)||(CONFIG_USE_RTOS==CONFIG_USE_RTOS_FREERTOS))
#error "Not Comptable RTOS"
#endif



#endif /* STM32_DRIVERS_CONFIGURATIONS_DRIVER_CONFIG_H_ */
