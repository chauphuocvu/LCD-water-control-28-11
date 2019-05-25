/*
			CHAU PHUOC VU
*/

#include "stm32f4xx_flash.h"
#include "uiappuser.h"
#include "DisplayNumber.h"

/** @defgroup FLASH_Sectors
  * @{
  */ 
#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< Sector Number 0 */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< Sector Number 1 */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< Sector Number 2 */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< Sector Number 3 */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< Sector Number 4 */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< Sector Number 5 */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< Sector Number 6 */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< Sector Number 7 */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< Sector Number 8 */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< Sector Number 9 */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< Sector Number 10 */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< Sector Number 11 */
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_Sector_0) || ((SECTOR) == FLASH_Sector_1) ||\
                                 ((SECTOR) == FLASH_Sector_2) || ((SECTOR) == FLASH_Sector_3) ||\
                                 ((SECTOR) == FLASH_Sector_4) || ((SECTOR) == FLASH_Sector_5) ||\
                                 ((SECTOR) == FLASH_Sector_6) || ((SECTOR) == FLASH_Sector_7) ||\
                                 ((SECTOR) == FLASH_Sector_8) || ((SECTOR) == FLASH_Sector_9) ||\
                                 ((SECTOR) == FLASH_Sector_10) || ((SECTOR) == FLASH_Sector_11))
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x080FFFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) < 0x1FFF7A0F))) 


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




#define	FLASH_ADDR_POOL_VOLUME											((uint32_t)0x08080000)
#define	FLASH_ADDR_FILTRATIONPERIOD									((uint32_t)0x08080001)
#define FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR 		((uint32_t)0x08080002)
#define FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY			((uint32_t)0x08080003)
#define	FLASH_ADDR_POOL_SELECT											((uint32_t)0x08080004)
#define	FLASH_ADDR_TEMP_SELECT											((uint32_t)0x08080005)
#define	FLASH_ADDR_WATER_HARDNESS_SELECT						((uint32_t)0x08080006)	
#define	FLASH_ADDR_TYPE_OF_PROBE										((uint32_t)0x08080007)
#define	FLASH_ADDR_LANGUAGE													((uint32_t)0x08080008)
#define	FLASH_ADDR_HOUR															((uint32_t)0x08080009)
#define	FLASH_ADDR_MIN															((uint32_t)0x0808000A)
#define	FLASH_ADDR_SEC															((uint32_t)0x0808000B)
#define	FLASH_ADDR_CALIBRATION_PROBE_PH							((uint32_t)0x0808000C)	
#define	FLASH_ADDR_CALIBRATION_PROBE_CLF						((uint32_t)0x08080014)	
#define FLASH_ADDR_REQUIRE_VALUE_PH									((uint32_t)0x0808001C)	
#define FLASH_ADDR_REQUIRE_VALUE_CLF								((uint32_t)0x08080024)
#define FLASH_ADDR_REQUIRE_VALUE_REDOX							((uint32_t)0x0808002C)
#define	FLASH_ADDR_TEMP_PH_CALIBRATION							((uint32_t)0x08080034)
#define	FLASH_ADDR_PH_V_CALIBRATION									((uint32_t)0x0808003C)
#define	FLASH_ADDR_SLOPE_CALIBRATION								((uint32_t)0x08080044)




uint8_t	  Read8bitDataFromFlash(uint32_t Address);
uint16_t	Read16bitDataFromFlash(uint32_t Address);
uint32_t	Read32bitDataFromFlash(uint32_t Address);
uint64_t	Read64bitDataFromFlash(uint32_t Address_H, uint32_t Address_L);
uint8_t	  ReadDataFromFlashForSelect(uint32_t Address);
/********************Write data for new chip*****************************/
void ReadSavedValue(void);
/****************************************************************/
uint8_t	SaveDataToFlash(void);
