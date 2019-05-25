/*
			CHAU PHUOC VU
*/



#include "flash_memory_driver.h"
#include "main.h"
#include "Sensor.h"

typedef struct {
uint32_t data_h;
uint32_t data_l;
} struct_64;

union	doubledata
{
	uint64_t int64bitdata;
	struct_64 struct64bit;
	double	doubledata;
}vu_doubledata;

union	floatdata
{
	uint32_t intdata;
	float	floatdata;
}vu_floatdata;

uint8_t	Read8bitDataFromFlash(uint32_t Address)
{
	uint8_t data = 0;
	data = *(__IO uint32_t*)Address;
	return data;
}


uint16_t	Read16bitDataFromFlash(uint32_t Address)
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


uint64_t	Read64bitDataFromFlash(uint32_t Address_H, uint32_t Address_L)
{
	uint64_t data = 0;
	uint32_t data_buf = 0;
	data_buf = *(__IO uint32_t*)Address_H;
	data = data_buf;
	data = data<<32;
	//Address += 4;
	data_buf = *(__IO uint32_t*)Address_L;
	data |= data_buf;
	return data;
}



uint8_t	ReadDataFromFlashForSelect(uint32_t Address)
{
	uint8_t data = 0;
	data = *(__IO uint32_t*)Address;
	if (data > 10)
		data = 0;
	return data;
}

FLASH_Status FLASH_Program64bitData(uint32_t Address, double data)
{
	vu_doubledata.doubledata = data;
	if (FLASH_ProgramWord(Address,vu_doubledata.struct64bit.data_h) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramWord(Address + 4,vu_doubledata.struct64bit.data_l) != FLASH_COMPLETE)	
		return 1;
	else return 1;
}


/*********************************************************/
void ReadSavedValue(void)
{
	PoolVolume = Read8bitDataFromFlash(FLASH_ADDR_POOL_VOLUME);
	if (PoolVolume == 0xFF)
		PoolVolume = 5;
	FiltrationPeriod = Read8bitDataFromFlash(FLASH_ADDR_FILTRATIONPERIOD);
	if (FiltrationPeriod == 0xFF)
		FiltrationPeriod = 10;
	RequireValueDosepH_DoseHour =	Read8bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR);
	if (RequireValueDosepH_DoseHour == 0xFF)
		RequireValueDosepH_DoseHour = 5;	
	RequireValueDosepH_DoseDay =	Read8bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY);
	if (RequireValueDosepH_DoseDay == 0xFF)
		RequireValueDosepH_DoseDay = 5;
	PoolSelect = ReadDataFromFlashForSelect(FLASH_ADDR_POOL_SELECT);
	Temperature = ReadDataFromFlashForSelect(FLASH_ADDR_TEMP_SELECT);
	WaterHardnessSelect = ReadDataFromFlashForSelect(FLASH_ADDR_WATER_HARDNESS_SELECT);
	TypeofProbe  = ReadDataFromFlashForSelect(FLASH_ADDR_TYPE_OF_PROBE);
	Languages_Choose = ReadDataFromFlashForSelect(FLASH_ADDR_LANGUAGE);
	hour =	Read8bitDataFromFlash(FLASH_ADDR_HOUR);
	if (hour > 24)
		hour = 0;
	min =	Read8bitDataFromFlash(FLASH_ADDR_MIN);
	if (min > 59)
		min = 0;	
	sec =	Read8bitDataFromFlash(FLASH_ADDR_SEC);
	if (sec > 59)
		sec = 0;
	vu_doubledata.int64bitdata = Read64bitDataFromFlash(FLASH_ADDR_CALIBRATION_PROBE_PH,FLASH_ADDR_CALIBRATION_PROBE_PH + 4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		Probe_pH = 4.0;
	else Probe_pH =	vu_doubledata.doubledata;
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_CALIBRATION_PROBE_CLF, FLASH_ADDR_CALIBRATION_PROBE_CLF+4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		Probe_CLF = 0.5;
	else Probe_CLF =	vu_doubledata.doubledata;
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_PH, FLASH_ADDR_REQUIRE_VALUE_PH + 4 );
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		RequireValuepH = 6.2;
	else RequireValuepH =	vu_doubledata.doubledata;
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_CLF, FLASH_ADDR_REQUIRE_VALUE_CLF +4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		RequireValueCLF = 0.5;
	else RequireValueCLF =	vu_doubledata.doubledata;
	RequireValueRedoxpH_Redox =	Read16bitDataFromFlash(FLASH_ADDR_REQUIRE_VALUE_REDOX);
	if (RequireValueRedoxpH_Redox == 0xFFFF)
		RequireValueRedoxpH_Redox = 0;
	/*Chau phuoc vu 17/5/2019*/
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_TEMP_PH_CALIBRATION, FLASH_ADDR_TEMP_PH_CALIBRATION + 4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		Probe_pH_temp = 25.0;
	else Probe_pH_temp =	vu_doubledata.doubledata;
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_PH_V_CALIBRATION, FLASH_ADDR_PH_V_CALIBRATION + 4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		pH_V_calibration = 0.11954;
	else pH_V_calibration =	vu_doubledata.doubledata;	
	vu_doubledata.int64bitdata =	Read64bitDataFromFlash(FLASH_ADDR_SLOPE_CALIBRATION, FLASH_ADDR_SLOPE_CALIBRATION + 4);
	if (vu_doubledata.int64bitdata == 0xFFFFFFFFFFFFFFFF)
		slope_calibration = 0.04669;
	else slope_calibration =	vu_doubledata.doubledata;	
	/*Chau Phuoc Vu 21/5/2019*/
	FiltrationPeriod_count = FiltrationPeriod;
	RequireValueDosepH_DoseHour_Display = RequireValueDosepH_DoseHour;
	RequireValueDosepH_DoseDay_Display = RequireValueDosepH_DoseDay;
 	PoolVolume_Display = PoolVolume;
 	FiltrationPeriod_Display = FiltrationPeriod;
 	RequireValueRedoxpH_Redox_Display = RequireValueRedoxpH_Redox;
	/*Chau phuoc vu 25/4/2019*/
 	RequireValuepH_Display = RequireValuepH;
 	RequireValueCLF_Display = RequireValueCLF;
}

/****************************************************************/
uint8_t	SaveDataToFlash(void)
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
	if (FLASH_ProgramByte(FLASH_ADDR_POOL_VOLUME,PoolVolume) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_FILTRATIONPERIOD,FiltrationPeriod) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR,RequireValueDosepH_DoseHour) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY,RequireValueDosepH_DoseDay) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_POOL_SELECT,PoolSelect) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_TEMP_SELECT,Temperature) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_WATER_HARDNESS_SELECT,WaterHardnessSelect) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_TYPE_OF_PROBE,TypeofProbe) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_LANGUAGE,Languages_Choose) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_HOUR,hour) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_MIN,min) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramByte(FLASH_ADDR_SEC,sec) != FLASH_COMPLETE)	
		return 1;
//	vu_doubledata.doubledata = Probe_pH;
	if (FLASH_Program64bitData(FLASH_ADDR_CALIBRATION_PROBE_PH,Probe_pH) != FLASH_COMPLETE)	
		return 1;
//	vu_mydata.floatdata = Probe_CLF;
	if (FLASH_Program64bitData(FLASH_ADDR_CALIBRATION_PROBE_CLF,Probe_CLF) != FLASH_COMPLETE)	
		return 1;
//	vu_mydata.floatdata = RequireValuepH;
	if (FLASH_Program64bitData(FLASH_ADDR_REQUIRE_VALUE_PH,RequireValuepH) != FLASH_COMPLETE)	
		return 1;	
//	vu_mydata.floatdata = RequireValueCLF;
	if (FLASH_Program64bitData(FLASH_ADDR_REQUIRE_VALUE_CLF,RequireValueCLF) != FLASH_COMPLETE)	
		return 1;
	if (FLASH_ProgramHalfWord(FLASH_ADDR_REQUIRE_VALUE_REDOX,RequireValueRedoxpH_Redox) != FLASH_COMPLETE)	
		return 1;
	/*chau phuoc vu 21/5/2019*/
//	vu_mydata.floatdata = Probe_pH_temp;
	if (FLASH_Program64bitData(FLASH_ADDR_TEMP_PH_CALIBRATION,Probe_pH_temp) != FLASH_COMPLETE)	
		return 1;
//	vu_mydata.floatdata = pH_V_calibration;
	if (FLASH_Program64bitData(FLASH_ADDR_PH_V_CALIBRATION,pH_V_calibration) != FLASH_COMPLETE)	
		return 1;
//	vu_mydata.floatdata = slope_calibration;
	if (FLASH_Program64bitData(FLASH_ADDR_SLOPE_CALIBRATION,slope_calibration) != FLASH_COMPLETE)	
		return 1;	
	FLASH_Lock(); 	
	return	0;	
}
