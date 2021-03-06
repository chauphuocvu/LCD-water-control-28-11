/*******************************************************************************
* @file		: uiframework.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Screen Declarations
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
#ifndef __UIFRAMEWORK_H
#define __UIFRAMEWORK_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "graphicObjectTypes.h"
#include "graphicObject.h"
#include "uiappuser.h"

/* Exported types --------------------------------------------------------------*/
extern GL_Page_TypeDef *CurrentScreen;
extern uint8_t DosingTest_Flag;

/*Added by Chau Phuoc Vu 23/11/2018*/
extern uint16_t		Screen;

#define	StartScreen_df																							1
#define	SettingsScreen_df																						2
#define	DosingTestScreen_df																					3
#define CalibrationAirScreen_df    																	4
#define TypeOfProbeScreen_df																				5
#define LanguagesScreen_df																					6
#define	ParametersScreen_df																					7
#define	ParametersPoolVolumeScreen_df																8
#define	ParametersFitrationPeriodScreen_df													9
#define	ParametersWaterScreen_df																		10
#define	WarningMaximalSafetyScreen_df																11
#define	WarningExtremeConditionScreen_df														12
#define	WarningProbeCalibration30_78Screen_df												13
#define	WarningWaterHardnessScreen_df																14
#define	WarningProbeCalibrationScreen_df														15
#define	WarningProbeCalibration70Screen_df													16
#define	WarningProbeCalibrationRequiredValueScreen_df								17
#define	WarningProbeCalibrationRequiredValueRedScreen_df						18
#define	WarningProbeCalibrationRequiredValueImpossibleScreen_df			19
#define	WarningTooRapidChangeScreen_df															20
#define ParametersRequireValuepHScreen_df														21
#define ParametersRequireValueCLFScreen_df 													22
#define CalibrationScreen_df 																				23
#define CalibrationpHProbeScreen_df																	24
#define CalibrationCLFProbeScreen_df 																25
#define ParametersRequireValueRedoxpH_RedoxScreen_df 								26
#define ParametersRequireValueRedoxpH_pHScreen_df 									27
#define ParametersRequireValueDosepH_DoseHourScreen_df							28
#define ParametersRequireValueDosepH_DoseHour_pHScreen_df						29
#define ParametersRequireValueDosepH_DoseDayScreen_df								30
#define ParametersRequireValueDosepH_DoseDay_pHScreen_df						31
#define CalibrationWaterScreen_df  																	32
#define WarningProbepHCalibrationScreen_df													33


/*Added by chau phuoc vu 14/11/2018*/
void DelayScreen(uint16_t time);
/* Exported constants ----------------------------------------------------------*/

#define DesignLabel01Color 					65535
#define DesignLabel02Color 					65535
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*Create Screen*/
void Create_StartScreen(void);
void Create_SettingsScreen(void);
/*Create DosingTest Screen*/
void Create_DosingTestScreen(void);
void Create_ParametersScreen(void);
void Create_ParametersPoolVolumeScreen(void);
void Create_ParametersFitrationPeriodScreen(void);
void Create_ParametersWaterScreen(void);
void Create_WarningMaximalSafetyScreen(void);
void Create_WarningExtremeConditionScreen(void);
void Create_WarningWaterHardnessScreen(void);
void Create_WarningProbeCalibration30_78Screen(void);
void Create_WarningProbeCalibrationScreen(void);
void Create_WarningProbeCalibration70Screen(void);
void Create_WarningProbeCalibrationRequiredValueScreen(void);
void Create_WarningProbeCalibrationRequiredValueRedScreen(void);
void Create_WarningProbeCalibrationRequiredValueImpossibleScreen(void);
void Create_WarningTooRapidChangeScreen(void);
void Create_ParametersRequireValuepHScreen(void);
void Create_ParametersRequireValueCLFScreen(void);
void Create_CalibrationScreen(void);
void Create_CalibrationpHProbeScreen(void);
void Create_CalibrationCLFProbeScreen(void);
void Create_ParametersRequireValueRedoxpH_RodexScreen(void);
void Create_ParametersRequireValueRedoxpH_pHScreen(void);
void Create_ParametersRequireValueDosepH_DoseHourScreen(void);
void Create_ParametersRequireValueDosepH_DoseHour_pHScreen(void);
void Create_ParametersRequireValueDosepH_DoseDayScreen(void);
void Create_ParametersRequireValueDosepH_DoseDay_pHScreen(void);
void Create_CalibrationWaterScreen(void);
void Create_CalibrationAirScreen(void);
void Create_TypeOfProbeScreen(void);
void Create_LanguagesScreen(void);

/*Show Screen*/
void Show_HomeScreen(void);
void Show_StartScreen(void);
void Show_SettingsScreen(void);
void Show_DosingTestScreen(void);
void Show_ParametersScreen(void);
void Show_ParametersPoolVolumeScreen(void);
void Show_ParametersFitrationPeriodScreen(void);
void Show_ParametersWaterScreen(void);
void Show_WarningMaximalSafetyScreen(void);
void Show_WarningExtremeConditionScreen(void);
void Show_WarningWaterHardnessScreen(void);
void Show_WarningProbeCalibration30_78Screen(void);
void Show_WarningProbeCalibrationScreen(void);
void Show_WarningProbeCalibration70Screen(void);
void Show_WarningProbeCalibrationRequiredValueScreen(void);
void Show_WarningProbeCalibrationrequiredValueRedScreen(void);
void Show_WarningProbeCalibrationRequiredValueImpossibleScreen(void);
void Show_WarningTooRapidChangeScreen(void);
void Show_ParametersRequireValuepHScreen(void);
void Show_ParametersRequireValueCLFScreen(void);
void Show_CalibrationScreen(void);
void Show_CalibrationpHProbeScreen(void);
void Show_CalibrationCLFProbeScreen(void);
void Show_ParametersRequireValueRedoxpH_RodexScreen(void);
void Show_ParametersRequireValueRedoxpH_pHScreen(void);
void Show_ParametersRequireValueDosepH_DoseHourScreen(void);
void Show_ParametersRequireValueDosepH_DoseHour_pHScreen(void);
void Show_ParametersRequireValueDosepH_DoseDayScreen(void);
void Show_ParametersRequireValueDosepH_DoseDay_pHScreen(void);
void Show_CalibrationWaterScreen(void);
void Show_CalibrationAirScreen(void);
void Show_TypeOfProbeScreen(void);
void Show_LanguagesScreen(void);
void Show_WarningProbepHCalibrationScreen(void);

#ifdef __cplusplus
}
#endif

#endif /*__UIFRAMEWORK_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

