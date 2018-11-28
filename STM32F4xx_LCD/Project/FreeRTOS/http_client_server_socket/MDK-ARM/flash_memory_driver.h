/*
			CHAU PHUOC VU
*/

#include "stm32f4xx_flash.h"


#define ADDR_FLASH_POOL        ((uint32_t)0x08080000) //luu gia tri thiet lap ve pool trong water parameter

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define	FLASH_USER_START_ADDR_DATA			ADDR_FLASH_SECTOR_8
#define	FLASH_USER_END_ADDR_DATA				ADDR_FLASH_SECTOR_9
#define	FLASH_ADDR_POOL_VOLUME					0x08080000	
#define	FLASH_ADDR_FILTRATIONPERIOD			0x08080002
#define	FLASH_ADDR_POOL_SELECT					0x08080004	
#define	FLASH_ADDR_TEMP_SELECT					0x08080006	
#define	FLASH_ADDR_WATER_HARDNESS_SELECT				0x08080008	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	
//#define	FLASH_USER_START_ADDR	


uint16_t	SaveHalfWordDataToFlash(uint32_t Address, uint16_t data);
uint16_t	ReadDataFromFlash(uint32_t Address);
uint16_t	ReadDataFromFlashForSelect(uint32_t Address);
