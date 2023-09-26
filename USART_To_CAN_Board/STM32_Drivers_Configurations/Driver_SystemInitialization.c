/*
 * File Name --> Driver_SystemInitialization.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Configurations
 * Brief	 --> Implementation of system initialization.
 * */


/*
==================================================
  Start Section --> File Includes
==================================================
*/
#include "HMCAL/Interrupt/InterruptHandlers.h"
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "Driver_Config.h"
#include "HMCAL/RCC/RCC.h"
#include "LMCAL/SYSTICK/SYSTICK.h"
#include "LMCAL/SCB/SCB.h"

/*
==================================================
  End   Section --> File Includes
==================================================
*/


/*
==================================================
  Start Section --> Function Definitions
==================================================
*/
void SystemInit(void){
	/*Configure FPU*/
#if CONFIG_USE_HARDWARE_FPU==1
	SCB_EnableFPU_v();
#endif
	/*Configure RCC*/
	RCC_InitClock_v();
	/*Init Systick*/
#if CONFIG_USE_RTOS==CONFIG_NO_RTOS
	SYSTICK_Init_v();
#endif
	/*Init Interrupt Handlers*/
	InterruptHandler_Init_v();

	/*Configure CRC*/
}
/*
==================================================
  End   Section --> Function Definitions
==================================================
*/
