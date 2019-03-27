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



uint8_t 		DosingTest_Flag = START_START;
uint8_t 		Languages_Choose;
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
float 	 		Probe_pH;
float 	 		Probe_CLF;
float 	 		RequireValuepH;
float 	 		RequireValueCLF;
int8_t   	RequireValueDosepH_DoseHour_Display;
int8_t 		RequireValueDosepH_DoseDay_Display;
uint16_t 		PoolVolume_Display;
uint16_t 		FiltrationPeriod_Display;
uint16_t 		CalibrationAir_Display;
uint16_t 		CalibrationWater_Display;
uint16_t 		RequireValueRedoxpH_Redox_Display;
float 	 		Probe_pH_Display;
float 		 	Probe_CLF_Display;
float 		 	RequireValuepH_Display;
float 		 	RequireValueCLF_Display;
	 

/*Start Screen */
void StartScreen_Setting(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
/*Settings Screen */
void SettingsScreen_Language(void)
{
	DestroyPage(CurrentScreen);
	Show_LanguagesScreen();
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
			DestroyPage(CurrentScreen);
	if (DosingTest_Flag != START_START)
		Create_DosingTestScreen();
	else;
	Show_DosingTestScreen();		
}
//////////////////////////////////////////////////////////////
void SettingsScreen_TypeOfProbe(void)
{
	DestroyPage(CurrentScreen);
	Show_TypeOfProbeScreen();
}
/////////////////////////////////////////////////////////////
void SettingsScreen_SaveData(void)
{
	SaveDataToFlash();
}





/*DosingTest Screen */
void DosingTestScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////
void DosingTestScreen_StartDisinf(void)
{
		switch (DosingTest_Flag)
	{
		case START_START:
			DosingTest_Flag = STOP_START;
		break;
		case START_STOP:
			DosingTest_Flag = STOP_STOP;	
		break;
		case STOP_START:
			DestroyPage(CurrentScreen);
			DosingTest_Flag = START_START;	
		break;
		case STOP_STOP :
			DosingTest_Flag = START_STOP;	
		break;
		default:
		break;
	}	
	Show_DosingTestScreen();

}
//////////////////////////////////////////////////////////////
void DosingTestScreen_StartPh(void)
{	
		switch (DosingTest_Flag)
	{
		case START_START:
			DosingTest_Flag = START_STOP;
		break;
		case START_STOP:
			DestroyPage(CurrentScreen);
			DosingTest_Flag = START_START;	
		break;
		case STOP_START:
			DosingTest_Flag = STOP_STOP;	
		break;
		case STOP_STOP :
			DosingTest_Flag = STOP_START;	
		break;
		default:
		break;
	}	
	Show_DosingTestScreen();
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
// Chon man hinh de hien thi dc set tu Type of Probe
	switch(TypeofProbe)
	{
		case FREECHLORINE:
			Show_ParametersRequireValuepHScreen();
			break;
		case REDOXPROBE:
			Show_ParametersRequireValueRedoxpH_RodexScreen();
			break;
		case MLPERHOUR:
			Show_ParametersRequireValueDosepH_DoseHourScreen();
			break;
		case MLPERDAY:
			Show_ParametersRequireValueDosepH_DoseDayScreen();
			break;
		default:
			break;
	}	
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
		PoolVolume_Display +=1;
	if (PoolVolume_Display > 50)
		PoolVolume_Display = 50;
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_dec(void)
{
		PoolVolume_Display -=1;
	if (PoolVolume_Display == 0)
		PoolVolume_Display = 0;
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_OK(void)
{
	PoolVolume = PoolVolume_Display;
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
		FiltrationPeriod_Display +=1;
	if (FiltrationPeriod_Display > 24)
		FiltrationPeriod_Display = 24;
}
	///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_dec(void)
{	
	FiltrationPeriod_Display -=1;
	if (FiltrationPeriod_Display == 6)
		FiltrationPeriod_Display = 6;		
}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_OK(void)
{
	FiltrationPeriod = FiltrationPeriod_Display;
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
	Show_ParametersScreen();
}
///////////////////////////////////////////////////////////////
void ParametersWaterScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Indoor(void)
{
	PoolSelect = INDOOR;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Outdoor(void)
{
	PoolSelect = OUTDOOR;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_ExtremeCondition(void)
{
	PoolSelect = EXTREME_CONDITION;
	DestroyPage(CurrentScreen);
	Show_WarningExtremeConditionScreen();
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Less20oC(void)
{
	Temperature = LESS20oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_20oC_30oC(void)
{
	Temperature = MIDDLE_20oC_30oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_More30oC(void)
{
	Temperature = MORE30oC;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Soft(void)
{
	WaterHardnessSelect = SOFT;
	DestroyPage(CurrentScreen);
	Show_WarningWaterHardnessScreen();
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_Hard(void)
{
	WaterHardnessSelect = HARD;
}
//////////////////////////////////////////////////////////////////
void ParametersWaterScreen_VeryHard(void)
{
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
	Show_CalibrationCLFProbeScreen();
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
		RequireValuepH_Display +=(float)0.1;
	if(RequireValuepH_Display > (float)7.6)
		RequireValuepH_Display = 7.6;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_dec(void)
{
		RequireValuepH_Display -=(float)0.1;
	if(RequireValuepH_Display < (float)6.5)
		RequireValuepH_Display = 6.5;	
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_OK(void)
{
	RequireValuepH = RequireValuepH_Display;
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
		RequireValueCLF_Display +=(float)0.1;
	if(RequireValueCLF_Display > (float)1.2)
		RequireValueCLF_Display = 1.2;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_dec(void)
{	
		RequireValueCLF_Display -=(float)0.1;
	if(RequireValueCLF_Display < (float)0.5)
		RequireValueCLF_Display = 0.5;
		
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_OK(void)
{
	RequireValueCLF = RequireValueCLF_Display;
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
		Probe_pH_Display +=(float)0.1;
	if(Probe_pH_Display > (float)7.8)
	{
		DestroyPage(CurrentScreen);
		Show_WarningProbeCalibration62_78Screen();
		Probe_pH_Display = 7.8;
	}
}
void CalibrationpHProbeScreen_dec(void)
{
		Probe_pH_Display -=(float)0.1;
	if(Probe_pH_Display < (float)6.2)
	{
		DestroyPage(CurrentScreen);
		Show_WarningProbeCalibration62_78Screen();
		Probe_pH_Display = 6.2;
	}
}
void CalibrationpHProbeScreen_OK(void)
{
	Probe_pH = Probe_pH_Display;
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
	Probe_CLF_Display +=(float)0.1;
	if (Probe_CLF_Display > (float)1.2)
		Probe_CLF_Display = 1.2;
}
void CalibrationCLFProbeScreen_dec(void)
{
		Probe_CLF_Display -=(float)0.1;
	if(Probe_CLF_Display == RequireValueCLF)
	{
		DestroyPage(CurrentScreen);
		Show_WarningProbeCalibrationrequiredValueRedScreen();
	}
	else if (Probe_CLF_Display < (float)0.5)
		Probe_CLF_Display = 0.5;
}
void CalibrationCLFProbeScreen_OK(void)
{
	Probe_CLF = Probe_CLF_Display;
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
		RequireValueRedoxpH_Redox_Display +=10;
	if(RequireValueRedoxpH_Redox_Display > 990)
		RequireValueRedoxpH_Redox_Display = 990;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_dec(void)
{
		RequireValueRedoxpH_Redox_Display -=10;
	if(RequireValueRedoxpH_Redox_Display < 10)
		RequireValueRedoxpH_Redox_Display = 10;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_RedoxScreen_OK(void)
{
	RequireValueRedoxpH_Redox = RequireValueRedoxpH_Redox_Display;
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
		RequireValuepH_Display +=(float)0.1;
	if(RequireValuepH_Display > (float)7.8)
		RequireValuepH_Display = 7.8;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_dec(void)
{
		RequireValuepH_Display -=(float)0.1;
	if(RequireValuepH_Display < (float)6.2)
		RequireValuepH_Display = 6.2;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueRedoxpH_pHScreen_OK(void)
{
	RequireValuepH = RequireValuepH_Display;
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
		RequireValueDosepH_DoseHour_Display +=1;
	if(RequireValueDosepH_DoseHour_Display > 20)
		RequireValueDosepH_DoseHour_Display = 20;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_dec(void)
{
		RequireValueDosepH_DoseHour_Display -=1;
	if(RequireValueDosepH_DoseHour_Display < 0)
		RequireValueDosepH_DoseHour_Display = 0;	
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHourScreen_OK(void)
{
	RequireValueDosepH_DoseHour = RequireValueDosepH_DoseHour_Display;
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
		RequireValuepH_Display +=(float)0.1;
	if(RequireValuepH_Display > (float)7.8)
		RequireValuepH_Display = 7.8;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_dec(void)
{
		RequireValuepH_Display -=(float)0.1;
	if(RequireValuepH_Display < (float)6.2)
		RequireValuepH_Display = 6.2;
		
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseHour_pHScreen_OK(void)
{
	RequireValuepH = RequireValuepH_Display;
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
		RequireValueDosepH_DoseDay_Display +=1;
	if(RequireValueDosepH_DoseDay_Display > 30)
		RequireValueDosepH_DoseDay_Display = 30;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_dec(void)
{
		RequireValueDosepH_DoseDay_Display -=1;
	if(RequireValueDosepH_DoseDay_Display < 0)
		RequireValueDosepH_DoseDay_Display = 0;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDayScreen_OK(void)
{
	RequireValueDosepH_DoseDay = RequireValueDosepH_DoseDay_Display;
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
		RequireValuepH_Display +=(float)0.1;
	if(RequireValuepH_Display > (float)7.8)
		RequireValuepH_Display = 7.8;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_dec(void)
{
		RequireValuepH_Display -=(float)0.1;
	if(RequireValuepH_Display < (float)6.2)
		RequireValuepH_Display = 6.2;
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueDosepH_DoseDay_pHScreen_OK(void)
{
	RequireValuepH = RequireValuepH_Display;
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
		CalibrationWater_Display +=1;
	if(CalibrationWater_Display < 40)
		CalibrationWater_Display = 40;
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_dec(void)
{
		CalibrationWater_Display -=1;
	if(CalibrationWater_Display == 0)
		CalibrationWater_Display = 0;
}
//////////////////////////////////////////////////////////////
void CalibrationWaterScreen_OK(void)
{
	CalibrationWater = CalibrationWater_Display;
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
		CalibrationAir_Display +=1;
	if(CalibrationAir_Display > 40)
		CalibrationAir_Display = 40;	
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_dec(void)
{	
		CalibrationAir_Display -=1;
	if(CalibrationAir_Display == 0)
		CalibrationAir_Display = 0;
}
//////////////////////////////////////////////////////////////
void CalibrationAirScreen_OK(void)
{
	CalibrationAir = CalibrationAir_Display;
}


/*TypeOfProbeScreen */
void TypeOfProbeScreen_Back(void)
{
	DestroyPage(CurrentScreen);
	Show_SettingsScreen();
}
void TypeOfProbeScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
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



/*LanguagesScreen */
void LanguagesScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	Show_StartScreen();
}
void LanguagesScreen_Vietnamese(void)
{
	Languages_Choose = VIETNAMESE;
}
void LanguagesScreen_English(void)
{
	Languages_Choose = ENGLISH;
}
