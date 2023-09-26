#include "BL_CommandExecutor.h"
#include "LIB/utils.h"
#include "HMCAL/DMA/DMA.h"
#include "LMCAL/SCB/SCB.h"
#include "LMCAL/SCB/SCB.h"


#if BOOTLOADER_TYPE == USART_BOOTLOADER

int main(void)
{
	/*
	 * Check if update flag is raised or image is not valid.
	 * If yes, initialize bootloader.
	 * Otherwise, Jump to application.
	 * */
	if (( UPDATE_FLAG_VALUE == UTILS_READ_ADDRESS(UPDATE_FLAG_ADDRESS))
			|| ( VALID_IMAGE_FLAG_VALUE != UTILS_READ_ADDRESS(VALID_IMAGE_FLAG_ADDRESS))){
		BL_Init_v();
		while(1){
			BL_Pooling_v();
		}
	}
	else{
		BL_Jump_To_App();
	}
	while(1){

	}
}

#elif BOOTLOADER_TYPE == CAN_BOOTLOADER

int main(void)
{
	BL_Init_v();

	while(1){
		BL_Pooling_v();
		if ((VALID_IMAGE_FLAG_VALUE) == (UTILS_READ_ADDRESS(VALID_IMAGE_FLAG_ADDRESS))){
			BL_Jump_To_App();
		}
	}
}

#else

#error "Please select available bootloader type"

#endif





