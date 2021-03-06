/*******************************************************************************
* @file		: uiappuser.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Event HandlerDeclarations
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
/* Define to prevent recursive inclusion -------------------------------------*/ 
#ifndef __UIAPPUSER_H
#define __UIAPPUSER_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Extern variable -------------------------------------------------------------*/
extern uint8_t 		Languages_Choose;


extern uint8_t 	  PoolVolume;
extern uint8_t 	  FiltrationPeriod;
extern uint8_t   	RequireValueDosepH_DoseHour;
extern uint8_t 		RequireValueDosepH_DoseDay;
extern uint8_t		PoolSelect;
extern uint8_t 		Temperature;
extern uint8_t 		WaterHardnessSelect;
extern uint8_t 		TypeofProbe;
extern uint8_t   	RequireValueDosepH_DoseHour_Display;
extern uint8_t 		RequireValueDosepH_DoseDay_Display;
extern uint8_t 		PoolVolume_Display;
extern uint8_t 		FiltrationPeriod_Display;

extern uint16_t 	RequireValueRedoxpH_Redox;
extern uint16_t 	RequireValueRedoxpH_Redox_Display;

extern double 	 		Probe_pH;
extern double 	 		Probe_CLF;
extern double 	 		RequireValuepH;
extern double 	 		RequireValueCLF;
extern uint16_t   RequireValueRedoxpH_Redox;
extern float 			CalibrationAir_Display;
extern float 			CalibrationWater_Display;
extern double 	 		Probe_pH_Display;
extern double 	 		Probe_CLF_Display;
extern double 	 		RequireValuepH_Display;
extern double 	 		RequireValueCLF_Display;
/*chau phuoc vu 25/4/2019*/

/*chau phuoc vu 17/5/2019*/
extern double 			Probe_pH_less_5;
extern double 			Probe_pH_more_5;
extern double 			pH_V_calibration_less_5_buffer;
extern double 			pH_V_calibration_more_5_buffer;
extern double 			Temp_calibration_less_5_buffer;
extern double 			Temp_calibration_more_5_buffer;

/* Define ----------------------------------------------------------*/
#define INDOOR								0
#define OUTDOOR								1
#define EXTREME_CONDITION			2
#define LESS20oC							0
#define MIDDLE_20oC_30oC			1
#define MORE30oC							2
#define SOFT									0
#define HARD									1
#define VERY_HARD							2
#define FREECHLORINE					0
#define REDOXPROBE						1
#define MLPERHOUR							2
#define MLPERDAY							3
#define ENGLISH								0
#define VIETNAMESE						1 
#define START_START						0
#define START_STOP						1
#define STOP_START						2
#define STOP_STOP							3
/*chau phuoc vu 23/4/2019*/
#define CALIBRATION_PH				0
#define NO_CALIBRATION_PH			1
#define CALIBRATION_RX				0
#define NO_CALIBRATION_RX			1
/*chau phuoc vu 21/5/2019*/
#define BACKTOSTART						1
#define BACK									0
extern uint8_t status_for_warning;
/*Start Screen */
void StartScreen_Setting(void);
/*Settings Screen */
void SettingsScreen_Language(void);
void SettingsScreen_BackToStart(void);
void SettingsScreen_Parameters(void);
void SettingsScreen_Calibration(void);
void SettingsScreen_DosingTest(void);
void SettingsScreen_TypeOfProbe(void);
void SettingsScreen_SaveData(void);
							
							
							
/*DosingTest Screen */
void DosingTestScreen_Back(void);
void DosingTestScreen_BackToStart(void);
void DosingTestScreen_StartDisinf(void);
void DosingTestScreen_StartPh(void);



/*Parameters Screen */
void ParametersScreen_Back(void);
void ParametersScreen_BackToStart(void);
void ParametersScreen_Pool(void);
void ParametersScreen_Water(void);
void ParametersScreen_pH(void);



/*ParametersVolumePool Screen */
void ParametersPoolVolumeScreen_Back(void);
void ParametersPoolVolumeScreen_BackToStart(void);
void ParametersPoolVolumeScreen_inc(void);
void ParametersPoolVolumeScreen_dec(void);
void ParametersPoolVolumeScreen_OK(void);
void ParametersPoolVolumeScreen_FiltrationPeriod(void);

/*ParametersFitrationPeriod Screen */
void ParametersFitrationPeriodScreen_Back(void);
void ParametersFitrationPeriodScreen_BackToStart(void);
void ParametersFitrationPeriodScreen_inc(void);
void ParametersFitrationPeriodScreen_dec(void);
void ParametersFitrationPeriodScreen_OK(void);
void ParametersFitrationPeriodScreen_PoolVolume(void);

/*ParametersWaterScreen */
void ParametersWaterScreen_Back(void);
void ParametersWaterScreen_BackToStart(void);
void ParametersWaterScreen_Indoor(void);
void ParametersWaterScreen_Outdoor(void);
void ParametersWaterScreen_ExtremeCondition(void);
void ParametersWaterScreen_Less20oC(void);
void ParametersWaterScreen_20oC_30oC(void);
void ParametersWaterScreen_More30oC(void);
void ParametersWaterScreen_Soft(void);
void ParametersWaterScreen_Hard(void);
void ParametersWaterScreen_VeryHard(void);




/* Warning Screen */
void WarningMaximalSafetyScreen_OK(void);
void WarningExtremeConditionScreen_OK(void);
void WarningWaterHardnessScreen_OK(void);
void WarningProbeCalibration30_78Screen_OK(void);
void WarningProbeCalibrationScreen_OK(void);
void WarningProbeCalibration70Screen_OK(void);
void WarningProbeCalibrationRequiredValueScreen_OK(void);
void WarningProbeCalibrationRequiredValueRedScreen_OK(void);
void WarningProbeCalibrationRequiredValueImpossibleScreen_OK(void);
void WarningTooRapidChangeScreen_CancelRestictions(void);
void WarningProbepHCalibrationScreen_NO(void);
void WarningProbepHCalibrationScreen_YES(void); 


/*ParametersRequireValuepH Screen */
void ParametersRequireValuepHScreen_Back(void);
void ParametersRequireValuepHScreen_BackToStart(void);
void ParametersRequireValuepHScreen_inc(void);
void ParametersRequireValuepHScreen_dec(void);
void ParametersRequireValuepHScreen_OK(void);
void ParametersRequireValuepHScreen_CLF(void);




/*ParametersRequireValueCLF Screen */
void ParametersRequireValueCLFScreen_Back(void);
void ParametersRequireValueCLFScreen_BackToStart(void);
void ParametersRequireValueCLFScreen_inc(void);
void ParametersRequireValueCLFScreen_dec(void);
void ParametersRequireValueCLFScreen_OK(void);
void ParametersRequireValueCLFScreen_pH(void);


/*Calibration Screen */
void CalibrationScreen_Back(void);
void CalibrationScreen_BackToStart(void);
void CalibrationScreen_CLFProbe(void);
void CalibrationScreen_pHProbe(void);
void CalibrationScreen_WaterThermometer(void);
void CalibrationScreen_AirThermometer(void);



/*CalibrationpHProbe Screen */
void CalibrationpHProbeScreen_Back(void);
void CalibrationpHProbeScreen_BackToStart(void);
void CalibrationpHProbeScreen_inc(void);
void CalibrationpHProbeScreen_dec(void);
void CalibrationpHProbeScreen_OK(void);



/*CalibrationCLFProbe Screen */
void CalibrationCLFProbeScreen_Back(void);
void CalibrationCLFProbeScreen_BackToStart(void);
void CalibrationCLFProbeScreen_inc(void);
void CalibrationCLFProbeScreen_dec(void);
void CalibrationCLFProbeScreen_OK(void);




/*ParametersRequireValueRedoxpH_Redox Screen */
void ParametersRequireValueRedoxpH_RedoxScreen_Back(void);
void ParametersRequireValueRedoxpH_RedoxScreen_BackToStart(void);
void ParametersRequireValueRedoxpH_RedoxScreen_inc(void);
void ParametersRequireValueRedoxpH_RedoxScreen_dec(void);
void ParametersRequireValueRedoxpH_RedoxScreen_OK(void);
void ParametersRequireValueRedoxpH_RedoxScreen_pH(void);




/*ParametersRequireValueRedoxpH_pHScreen */
void ParametersRequireValueRedoxpH_pHScreen_Back(void);
void ParametersRequireValueRedoxpH_pHScreen_BackToStart(void);
void ParametersRequireValueRedoxpH_pHScreen_inc(void);
void ParametersRequireValueRedoxpH_pHScreen_dec(void);
void ParametersRequireValueRedoxpH_pHScreen_OK(void);
void ParametersRequireValueRedoxpH_pHScreen_Rodex(void);




/*ParametersRequireValueDosepH_DoseHour Screen */
void ParametersRequireValueDosepH_DoseHourScreen_Back(void);
void ParametersRequireValueDosepH_DoseHourScreen_BackToStart(void);
void ParametersRequireValueDosepH_DoseHourScreen_inc(void);
void ParametersRequireValueDosepH_DoseHourScreen_dec(void);
void ParametersRequireValueDosepH_DoseHourScreen_OK(void);
void ParametersRequireValueDosepH_DoseHourScreen_pH(void);



/*ParametersRequireValueDosepH_DoseHour_pH Screen */
void ParametersRequireValueDosepH_DoseHour_pHScreen_Back(void);
void ParametersRequireValueDosepH_DoseHour_pHScreen_BackToStart(void);
void ParametersRequireValueDosepH_DoseHour_pHScreen_inc(void);
void ParametersRequireValueDosepH_DoseHour_pHScreen_dec(void);
void ParametersRequireValueDosepH_DoseHour_pHScreen_OK(void);
void ParametersRequireValueDosepH_DoseHour_pHScreen_Dose(void);



/*ParametersRequireValueDosepH_DoseDay Screen */
void ParametersRequireValueDosepH_DoseDayScreen_Back(void);
void ParametersRequireValueDosepH_DoseDayScreen_BackToStart(void);
void ParametersRequireValueDosepH_DoseDayScreen_inc(void);
void ParametersRequireValueDosepH_DoseDayScreen_dec(void);
void ParametersRequireValueDosepH_DoseDayScreen_OK(void);
void ParametersRequireValueDosepH_DoseDayScreen_pH(void);



/*ParametersRequireValueDosepH_DoseDay_pH Screen */
void ParametersRequireValueDosepH_DoseDay_pHScreen_Back(void);
void ParametersRequireValueDosepH_DoseDay_pHScreen_BackToStart(void);
void ParametersRequireValueDosepH_DoseDay_pHScreen_inc(void);
void ParametersRequireValueDosepH_DoseDay_pHScreen_dec(void);
void ParametersRequireValueDosepH_DoseDay_pHScreen_OK(void);
void ParametersRequireValueDosepH_DoseDay_pHScreen_Dose(void);




/*CalibrationWaterScreen */
void CalibrationWaterScreen_Back(void);
void CalibrationWaterScreen_BackToStart(void);
void CalibrationWaterScreen_inc(void);
void CalibrationWaterScreen_dec(void);
void CalibrationWaterScreen_OK(void);



/*TypeOfProbeScreen */
void TypeOfProbeScreen_Back(void);
void TypeOfProbeScreen_BackToStart(void);
void TypeOfProbeScreen_FreeChlorine(void);
void TypeOfProbeScreen_RedoxProbe(void);
void TypeOfProbeScreen_mlperhour(void);
void TypeOfProbeScreen_mlperday(void);




/*CalibrationAirScreen */
void CalibrationAirScreen_Back(void);
void CalibrationAirScreen_BackToStart(void);
void CalibrationAirScreen_inc(void);
void CalibrationAirScreen_dec(void);
void CalibrationAirScreen_OK(void);



/*LanguagesScreen */
void LanguagesScreen_BackToStart(void);
void LanguagesScreen_Vietnamese(void);
void LanguagesScreen_English(void);



#ifdef __cplusplus
}
#endif

#endif /*__UIAPPUSER_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

