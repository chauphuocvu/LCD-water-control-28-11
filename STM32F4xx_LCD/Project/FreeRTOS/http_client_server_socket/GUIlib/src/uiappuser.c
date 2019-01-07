/*******************************************************************************
* @file		: uiappuser.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Event Handlers
*******************************************************************************/
/* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
*******************************************************************************
*/ 
/*includes----------------------------------------------------------------------*/
#include "uiframework.h"
#include "uiappuser.h"
#include "LcdHal.h"
#include "stm32f4xx_uartstdio.h"
#include "flash_memory_driver.h"
/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup User_Functions
  * @brief Contains event handlers for controls to execute the user code
  * @{
  */

DosingTest DosingTest_Flag = StartStart;
uint8_t 		PoolSelect;
uint8_t 		Temperature;
uint8_t 		WaterHardnessSelect;
uint8_t 		TypeofProbe;
uint8_t   	RequireValueDosepH_DoseHour;
uint8_t 		RequireValueDosepH_DoseDay;
uint16_t 		PoolVolume;
uint16_t 		FiltrationPeriod;
uint16_t 		CalibrationAir;
uint16_t 		CalibrationWater;
uint16_t 		RequireValueRedoxpH_Redox;
double 	 		RequireValueDosepH_DoseHour_pH;
double	 		RequireValueDosepH_DoseDay_pH;
double 	 		Probe_pH;
double 	 		Probe_CLF;
double 	 		RequireValuepH;
double 	 		RequireValueCLF;
double 	 		RequireValueRedoxpH_pH;
	 
/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
#define INDOOR			0
#define OUTDOOR			1
#define EXTREME_CONDITION			2
#define LESS20oC		0
#define MIDDLE_20oC_30oC	1
#define MORE30oC			2
#define SOFT			0
#define HARD			1
#define VERY_HARD			2
#define FREECHLORINE	0
#define REDOXPROBE	1
#define MLPERHOUR	2
#define MLPERDAY	3

/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/
/*Start Screen */
void StartScreen_Setting(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
/*Settings Screen */
void SettingsScreen_Language(void)
{
}
////////////////////////////////////////////////////////////
void SettingsScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void SettingsScreen_Parameters(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void SettingsScreen_Calibration(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationScreen();
}
//////////////////////////////////////////////////////////////
void SettingsScreen_DosingTest(void)
{
	switch (DosingTest_Flag)
	{
		case StartStart:
			DestroyPage(CurrentScreen);
			Show_DosingTestStartStartScreen();		
		break;
		case StartStop:
			DestroyPage(CurrentScreen);
			Show_DosingTestStartStopScreen();		
		break;
		case StopStart:
			DestroyPage(CurrentScreen);			
			Show_DosingTestStopStartScreen();	
		break;
		case StopStop :
			DestroyPage(CurrentScreen);
			Show_DosingTestStopStopScreen();	
		break;
	}	
}
//////////////////////////////////////////////////////////////
void SettingsScreen_TypeOfProbe(void)
{
	DestroyPage(CurrentScreen);
	Show_TypeOfProbeScreen();
}





/*DosingTest Screen */
void DosingTestStartStartScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
	DosingTest_Flag = StartStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
	DosingTest_Flag = StartStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_StartDisinf(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStopStartScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestStartStartScreen_StartPh(void)
{	
	DestroyPage(CurrentScreen);
	Show_DosingTestStartStopScreen();
}
/*DosingTestStopStart Screen */
void DosingTestStopStartScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
	DosingTest_Flag = StopStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_BackToStart(void)
{	
	DestroyPage(CurrentScreen);
	Show_StartScreen();
	DosingTest_Flag = StartStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_StopDisinf(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStartStartScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestStopStartScreen_StartPh(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStopStopScreen();
}
/*DosingTestStopStop Screen */
void DosingTestStopStopScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
	DosingTest_Flag = StopStop;
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
	DosingTest_Flag = StartStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_StopDisinf(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStartStopScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestStopStopScreen_StopPh(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStopStartScreen();
}
/*DosingTestStartStop Screen */
void DosingTestStartStopScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
	DosingTest_Flag = StartStop;
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
	DosingTest_Flag = StartStart;
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_StartDisinf(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStopStartScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestStartStopScreen_StopPh(void)
{
	DestroyPage(CurrentScreen);
	Show_DosingTestStartStartScreen();
}








/*Parameters Screen */
void ParametersScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
////////////////////////////////////////////////////////////
void ParametersScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersScreen_Pool(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersPoolVolumeScreen();
}
//////////////////////////////////////////////////////////////
void ParametersScreen_Water(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}
////////////////////////////////////////////////////////////
void ParametersScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValuepHScreen();
}




/*ParametersPoolVolumePool Screen */
void ParametersPoolVolumeScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_inc(void)
{
	PoolVolume +=1;
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_dec(void)
{
	PoolVolume -=1;
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_POOL_VOLUME,PoolVolume);
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_FiltrationPeriod(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersFitrationPeriodScreen();
}



/*ParametersFitrationPeriod Screen */
void ParametersFitrationPeriodScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_inc(void)
{
	FiltrationPeriod +=1;
}
	///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_dec(void)
{
	FiltrationPeriod -=1;
}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_FILTRATIONPERIOD,FiltrationPeriod);
}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_PoolVolume(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersPoolVolumeScreen();
}




/*ParametersWaterScreen */
void ParametersWaterScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	SaveHalfWordDataToFlash(FLASH_ADDR_POOL_SELECT,PoolSelect);
	SaveHalfWordDataToFlash(FLASH_ADDR_TEMP_SELECT,Temperature);
	SaveHalfWordDataToFlash(FLASH_ADDR_WATER_HARDNESS_SELECT,WaterHardnessSelect);
	Show_ParametersScreen();
}
///////////////////////////////////////////////////////////////
void ParametersWaterScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	SaveHalfWordDataToFlash(FLASH_ADDR_POOL_SELECT,PoolSelect);
	SaveHalfWordDataToFlash(FLASH_ADDR_TEMP_SELECT,Temperature);
	SaveHalfWordDataToFlash(FLASH_ADDR_WATER_HARDNESS_SELECT,WaterHardnessSelect);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Indoor(void)
{
	UARTprintf("ParametersWaterScreen_Indoor\r\n");
	PoolSelect = INDOOR;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Outdoor(void)
{
	UARTprintf("ParametersWaterScreen_Outdoor\r\n");
	PoolSelect = OUTDOOR;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_ExtremeCondition(void)
{
	UARTprintf("ParametersWaterScreen_ExtremeCondition\r\n");
	PoolSelect = EXTREME_CONDITION;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Less20oC(void)
{
	UARTprintf("ParametersWaterScreen_Less20oC\r\n");
	Temperature = LESS20oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_20oC_30oC(void)
{
	UARTprintf("ParametersWaterScreen_20oC_30oC\r\n");
	Temperature = MIDDLE_20oC_30oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_More30oC(void)
{
	UARTprintf("ParametersWaterScreen_More30oC\r\n");
	Temperature = MORE30oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Soft(void)
{
	UARTprintf("ParametersWaterScreen_Soft\r\n");
	WaterHardnessSelect = SOFT;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Hard(void)
{
	UARTprintf("ParametersWaterScreen_Hard\r\n");
	WaterHardnessSelect = HARD;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_VeryHard(void)
{
	UARTprintf("ParametersWaterScreen_VeryHard\r\n");
	WaterHardnessSelect = VERY_HARD;
}



/* WarningMaximalSafetyScreen */
void WarningMaximalSafetyScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}


void WarningExtremeConditionScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}


void WarningWaterHardnessScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}


void WarningProbeCalibration62_78Screen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationpHProbeScreen();
}


void WarningProbeCalibrationScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationpHProbeScreen();
}

void WarningProbeCalibration70Screen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationpHProbeScreen();
}

void WarningProbeCalibrationRequiredValueScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationCLFProbeScreen();
}

void WarningProbeCalibrationRequiredValueRedScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}


void WarningProbeCalibrationRequiredValueImpossibleScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}

void WarningTooRapidChangeScreen_CancelRestictions(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}




/*ParametersRequireValuepH Screen */
void ParametersRequireValuepHScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_inc(void)
{
	RequireValuepH +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_dec(void)
{
	RequireValuepH -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_PH,RequireValuepH);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_CLF(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueCLFScreen();
}




/*ParametersRequireValueCLF Screen */
void ParametersRequireValueCLFScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_inc(void)
{
	RequireValueCLF +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_dec(void)
{
	RequireValueCLF -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_CLF,RequireValueCLF);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValuepHScreen();
}

/*Calibration Screen */
void CalibrationScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
void CalibrationScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
void CalibrationScreen_CLFProbe(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationCLFProbeScreen();
	DestroyPage(CurrentScreen);
	Show_WarningProbeCalibrationRequiredValueScreen();
}
void CalibrationScreen_pHProbe(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationpHProbeScreen();
	DestroyPage(CurrentScreen);
	Show_WarningProbeCalibration70Screen();	
}
void CalibrationScreen_WaterThermometer(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationWaterScreen();
}
void CalibrationScreen_AirThermometer(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationAirScreen();
}


/*CalibrationpHProbe Screen */
void CalibrationpHProbeScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationScreen();
}
void CalibrationpHProbeScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
void CalibrationpHProbeScreen_inc(void)
{
	Probe_pH +=0.1;
}
void CalibrationpHProbeScreen_dec(void)
{
	Probe_pH -=0.1;
}
void CalibrationpHProbeScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_CALIBRATION_PROBE_PH,Probe_pH);
}




/*CalibrationCLFProbe Screen */
void CalibrationCLFProbeScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationScreen();
}
void CalibrationCLFProbeScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
void CalibrationCLFProbeScreen_inc(void)
{
	Probe_CLF +=0.1;
}
void CalibrationCLFProbeScreen_dec(void)
{
	Probe_CLF -=0.1;
}
void CalibrationCLFProbeScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_CALIBRATION_PROBE_CLF,Probe_CLF);
}


/*ParametersRequireValueRedoxpH_Redox Screen */
void ParametersRequireValueRedoxpH_RedoxScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_inc(void)
{
	RequireValueRedoxpH_Redox +=1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_dec(void)
{
	RequireValueRedoxpH_Redox -=1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_REDOX,RequireValueRedoxpH_Redox);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueRedoxpH_pHScreen();
}



/*ParametersRequireValueRedoxpH_pH Screen */
void ParametersRequireValueRedoxpH_pHScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_inc(void)
{
	RequireValueRedoxpH_pH +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_dec(void)
{
	RequireValueRedoxpH_pH -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_REDOX_PH,RequireValueRedoxpH_pH);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_Rodex(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueRedoxpH_RodexScreen();
}



/*ParametersRequireValueDosepH_DoseHour Screen */
void ParametersRequireValueDosepH_DoseHourScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_inc(void)
{
	RequireValueDosepH_DoseHour +=1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_dec(void)
{
	RequireValueDosepH_DoseHour -=1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEHOUR,RequireValueDosepH_DoseHour);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueDosepH_DoseHour_pHScreen();
}



/*ParametersRequireValueDosepH_DoseHour_pH Screen */
void ParametersRequireValueDosepH_DoseHour_pHScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_inc(void)
{
	RequireValueDosepH_DoseHour_pH +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_dec(void)
{
	RequireValueDosepH_DoseHour_pH -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEHOUR_PH,RequireValueDosepH_DoseHour_pH);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_Dose(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueDosepH_DoseHourScreen();
}



/*ParametersRequireValueDosepH_DoseDay Screen */
void ParametersRequireValueDosepH_DoseDayScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_inc(void)
{
	RequireValueDosepH_DoseDay +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_dec(void)
{
	RequireValueDosepH_DoseDay -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY,RequireValueDosepH_DoseDay);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueDosepH_DoseDay_pHScreen();
}



/*ParametersRequireValueDosepH_DoseDay_pH Screen */
void ParametersRequireValueDosepH_DoseDay_pHScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_inc(void)
{
	RequireValueDosepH_DoseDay_pH +=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_dec(void)
{
	RequireValueDosepH_DoseDay_pH -=0.1;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_OK(void)
{
	SaveDoubleWordDataToFlash(FLASH_ADDR_REQUIRE_VALUE_DOSEPH_DOSEDAY_PH,RequireValueDosepH_DoseDay_pH);
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_Dose(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValueDosepH_DoseDayScreen();
}


/*CalibrationWater Screen */
void CalibrationWaterScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationScreen();
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_inc(void)
{
	CalibrationWater +=1;
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_dec(void)
{
	CalibrationWater -=1;
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_CALIBRATION_WATER,CalibrationWater);
}


/*CalibrationAir Screen */
void CalibrationAirScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_CalibrationScreen();
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_inc(void)
{
	CalibrationAir +=1; 
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_dec(void)
{
	CalibrationAir -=1;
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_OK(void)
{
	SaveHalfWordDataToFlash(FLASH_ADDR_CALIBRATION_AIR,CalibrationAir);
}


/*TypeOfProbeScreen */
void TypeOfProbeScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	SaveHalfWordDataToFlash(FLASH_ADDR_TYPE_OF_PROBE,TypeofProbe);
	Show_SettingsScreen();
}
void TypeOfProbeScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	SaveHalfWordDataToFlash(FLASH_ADDR_TYPE_OF_PROBE,TypeofProbe);
	Show_StartScreen();
}
void TypeOfProbeScreen_FreeChlorine(void)
{
	TypeofProbe = FREECHLORINE;
}
void TypeOfProbeScreen_RedoxProbe(void)
{
	TypeofProbe = REDOXPROBE;
}
void TypeOfProbeScreen_mlperhour(void)
{
	TypeofProbe = MLPERHOUR;
}
void TypeOfProbeScreen_mlperday(void)
{
	TypeofProbe = MLPERDAY;
}
