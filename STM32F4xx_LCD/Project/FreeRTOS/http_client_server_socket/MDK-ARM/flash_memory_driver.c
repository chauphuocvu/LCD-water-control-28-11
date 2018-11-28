/*
			CHAU PHUOC VU
*/



#include "flash_memory_driver.h"


uint16_t	SaveHalfWordDataToFlash(uint32_t Address, uint16_t data)
{
	 FLASH_Unlock();
	 /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	if (FLASH_ProgramHalfWord(Address,data) != FLASH_COMPLETE)	
		return 1;
		FLASH_Lock(); 	
	return	0;	
}

uint16_t	ReadDataFromFlash(uint32_t Address)
{
	uint16_t data = 0;
	data = *(__IO uint32_t*)Address;
	return data;
}
uint16_t	ReadDataFromFlashForSelect(uint32_t Address)
{
	uint16_t data = 0;
	data = *(__IO uint32_t*)Address;
	if (data > 2)
		data = 0;
	return data;
}
