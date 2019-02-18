/*
			CHAU PHUOC VU
*/



#include "flash_memory_driver.h"




union	data
{
	uint32_t intdata;
	float	floatdata;
}vu_mydata;



uint16_t	ReadDataFromFlash(uint32_t Address)
{
	uint16_t data = 0;
	data = *(__IO uint32_t*)Address;
	return data;
}




uint32_t	Read32bitDataFromFlash(uint32_t Address)
{
	uint32_t data = 0;
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




/*********************************************************/
void ReadSavedValue(void)
{
	Languages_Choose = ReadDataFromFlashForSelect(FLASH_ADDR_LANGUAGE);
	PoolSelect = ReadDataFromFlashForSelect(FLASH_ADDR_POOL_SELECT);
	Temperature = ReadDataFromFlashForSelect(FLASH_ADDR_TEMP_SELECT);
	TypeofProbe  = ReadDataFromFlashForSelect(FLASH_ADDR_TYPE_OF_PROBE);
	WaterHardnessSelect = ReadDataFromFlashForSelect(FLASH_ADDR_WATER_HARDNESS_SELECT);
	RequireValueDosepH_DoseHour =	ReadDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR);
	RequireValueDosepH_DoseDay =	ReadDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY);
	CalibrationAir =	ReadDataFromFlash(FLASH_ADDR_CALIBRATION_AIR);
	CalibrationWater =	ReadDataFromFlash(FLASH_ADDR_CALIBRATION_WATER);
	RequireValueRedoxpH_Redox =	ReadDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_REDOX);
	
	vu_mydata.intdata = Read32bitDataFromFlash(FLASH_ADDR_CALIBRATION_PROBE_PH);
	if (vu_mydata.intdata == 0xFFFFFFFF)
		Probe_pH = 6.2;
	else Probe_pH =	vu_mydata.floatdata;
	vu_mydata.intdata =	Read32bitDataFromFlash(FLASH_ADDR_CALIBRATION_PROBE_CLF);
	if (vu_mydata.intdata == 0xFFFFFFFF)
		Probe_CLF = 0.5;
	else Probe_CLF =	vu_mydata.floatdata;
	vu_mydata.intdata =	Read32bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_PH);
	if (vu_mydata.intdata == 0xFFFFFFFF)
		RequireValuepH = 6.2;
	else RequireValuepH =	vu_mydata.floatdata;
	vu_mydata.intdata =	Read32bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_CLF);
	if (vu_mydata.intdata == 0xFFFFFFFF)
		RequireValueCLF = 0.5;
	else RequireValueCLF =	vu_mydata.floatdata;
	
	
	PoolVolume = ReadDataFromFlash(FLASH_ADDR_POOL_VOLUME);
	FiltrationPeriod = ReadDataFromFlash(FLASH_ADDR_FILTRATIONPERIOD);
	RequireValueDosepH_DoseHour_Display = RequireValueDosepH_DoseHour;
	RequireValueDosepH_DoseDay_Display = RequireValueDosepH_DoseDay;
 	PoolVolume_Display = PoolVolume;
 	FiltrationPeriod_Display = FiltrationPeriod;
 	CalibrationAir_Display = CalibrationAir;
 	CalibrationWater_Display = CalibrationWater;
 	RequireValueRedoxpH_Redox_Display = RequireValueRedoxpH_Redox;
 	Probe_pH_Display = Probe_pH;
 	Probe_CLF_Display = Probe_CLF;
 	RequireValuepH_Display = RequireValuepH;
 	RequireValueCLF_Display = RequireValueCLF;
}

/****************************************************************/
uint16_t	SaveDataToFlash(void)
{
	FLASH_Unlock();
		/* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will be done by word */ 
  if (FLASH_EraseSector(FLASH_Sector_8, VoltageRange_3) != FLASH_COMPLETE)
  { 
    /* Error occurred while sector erase. 
    User can add here some code to deal with this error  */
    return	1;
  }
	if (FLASH_ProgramHalfWord(FLASH_ADDR_POOL_VOLUME,PoolVolume) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_FILTRATIONPERIOD,FiltrationPeriod) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_POOL_SELECT,PoolSelect) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_TEMP_SELECT,Temperature) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_WATER_HARDNESS_SELECT,WaterHardnessSelect) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_TYPE_OF_PROBE,TypeofProbe) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_CALIBRATION_AIR,CalibrationAir) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_CALIBRATION_WATER,CalibrationWater) != FLASH_COMPLETE)	
		return 1;
	vu_mydata.floatdata = Probe_pH;
	if (FLASH_ProgramWord(FLASH_ADDR_CALIBRATION_PROBE_PH,vu_mydata.intdata) != FLASH_COMPLETE)	
		return 1;
	vu_mydata.floatdata = Probe_CLF;
	if (FLASH_ProgramWord(FLASH_ADDR_CALIBRATION_PROBE_CLF,vu_mydata.intdata) != FLASH_COMPLETE)	
		return 1;
	vu_mydata.floatdata = RequireValuepH;
	if (FLASH_ProgramWord(FLASH_ADDR_REQUIRE_VALUE_PH,vu_mydata.intdata) != FLASH_COMPLETE)	
		return 1;
	vu_mydata.floatdata = RequireValueCLF;
	if (FLASH_ProgramWord(FLASH_ADDR_REQUIRE_VALUE_CLF,vu_mydata.intdata) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_REQUIRE_VALUE_REDOX,RequireValueRedoxpH_Redox) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR,RequireValueDosepH_DoseHour) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY,RequireValueDosepH_DoseDay) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_LANGUAGE,Languages_Choose) != FLASH_COMPLETE)	
		return 1;
		FLASH_Lock(); 	
	return	0;	
}