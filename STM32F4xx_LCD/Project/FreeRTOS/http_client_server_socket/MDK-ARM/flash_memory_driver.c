/*
			CHAU PHUOC VU
*/



#include "flash_memory_driver.h"
#include "uiappuser.h"

uint16_t	SaveHalfWordDataToFlash(uint32_t Address, uint16_t data)
{
	FLASH_Unlock();
	 /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
//    if (FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3) != FLASH_COMPLETE)
//    { 
//      /* Error occurred while sector erase. 
//         User can add here some code to deal with this error  */
//      return	1;
//    }
	if (FLASH_ProgramHalfWord(Address,data) != FLASH_COMPLETE)	
		return 1;
		FLASH_Lock(); 	
	return	0;	
}


uint16_t	SaveDoubleWordDataToFlash(uint32_t Address, double data)
{
	FLASH_Unlock();
	 /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	if (FLASH_ProgramDoubleWord(Address,data) != FLASH_COMPLETE)	
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
	if (data > 10)
		data = 0;
	return data;
}
