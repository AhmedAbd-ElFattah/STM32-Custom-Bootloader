/*
 * File Name --> Driver_ClockConfig.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Configurations
 * Brief	 --> Configurations of system clock.
 * */

#ifndef STM32_DRIVERS_CONFIGURATIONS_DRIVER_CLOCKCONFIG_H_
#define STM32_DRIVERS_CONFIGURATIONS_DRIVER_CLOCKCONFIG_H_


/*
==================================================
  Start Section --> File Includes
==================================================
*/

/*
==================================================
  End   Section --> File Includes
==================================================
*/


/*
==================================================
  Start Section --> Macro Declaration
==================================================
*/
/********************** Define Clock Frequencies **********************/
#define				CLOCK_HSI_RC													16
#define				CLOCK_HSE_RC													16

/********************** Define Clock Prescallers parameters **********************/

/* Range for CLOCK_PLL_M is from 2 to 63 */
#define				CLOCK_PLL_M														8
/* Range for CLOCK_PLL_N is from 50 to 432 */
#define				CLOCK_PLL_N														72
/* Range for CLOCK_PLL_P is 2, 4, 6, 8 only */
#define				CLOCK_PLL_P														2
/* Range for CLOCK_PLL_Q is from 2 to 15 */
#define				CLOCK_PLL_Q														4

/* CLOCK_AHB_PRESCALER
 * Available options are 1, 2, 4, 8, 16, 64, 128, 256, and 512
 * */
#define				CLOCK_AHB_PRESCALER												1

/* CLOCK_PRESCALLER_TO_CORTEX_SYSTEM_TIMER
 * Available options is 1 or 8
 * */
#define				CLOCK_PRESCALLER_TO_CORTEX_SYSTEM_TIMER							8

/* CLOCK_APB1_PRESCALER
 * Available options is 1,2,4,8,or 16
 * */
#define				CLOCK_APB1_PRESCALER											1

/* CLOCK_APB2_PRESCALER
 * Available options is 1,2,4,8,or 16
 * */
#define				CLOCK_APB2_PRESCALER											1

/* Select PLL Clock Source.
 * Available Options
 * 					CLOCK_PLL_SOURCE_HSI
 * 					CLOCK_PLL_SOURCE_HSE
 * 	*/
#define				CLOCK_PLL_SOURCE_MUX											CLOCK_PLL_SOURCE_HSI

/* Select System Clock Source.
 * Available Options
 * 					CLOCK_SYSTEM_CLOCK_MUX_HSI
 * 					CLOCK_SYSTEM_CLOCK_MUX_HSE
 * 					CLOCK_SYSTEM_CLOCK_MUX_PLLCLK
 */
#define				CLOCK_SYSTEM_CLOCK_MUX											CLOCK_SYSTEM_CLOCK_MUX_HSI

/*
==================================================
  End   Section --> Macro Declaration
==================================================
*/

#endif /* STM32_DRIVERS_CONFIGURATIONS_DRIVER_CLOCKCONFIG_H_ */
