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

/* Exported types --------------------------------------------------------------*/
extern GL_Page_TypeDef *CurrentScreen;
extern GL_Page_TypeDef StartScreen;
extern GL_Page_TypeDef SettingsScreen;
extern GL_Page_TypeDef DosingTestStartStartScreen;
extern GL_Page_TypeDef DosingTestStopStartScreen;
extern GL_Page_TypeDef DosingTestStopStopScreen;
extern GL_Page_TypeDef DosingTestStartStopScreen;
extern GL_Page_TypeDef ParametersScreen;
extern GL_Page_TypeDef ParametersPoolVolumeScreen;
extern GL_Page_TypeDef ParametersFitrationPeriodScreen;
extern GL_Page_TypeDef ParametersWaterScreen;
extern GL_Page_TypeDef WarningMaximalSafetyScreen;



/*Added by Chau Phuoc Vu 23/11/2018*/
extern uint16_t		Screen;

#define	StartScreen_df			1
#define	SettingsScreen_df			2
#define	DosingTestStartStartScreen_df			3
#define	DosingTestStopStartScreen_df			4
#define	DosingTestStopStopScreen_df			5
#define	DosingTestStartStopScreen_df			6
#define	ParametersScreen_df			7
#define	ParametersPoolVolumeScreen_df			8
#define	ParametersFitrationPeriodScreen_df			9
#define	ParametersWaterScreen_df			10
#define	WarningMaximalSafetyScreen_df			11
#define	WarningExtremeConditionScreen_df			12
#define	WarningProbeCalibration62_78Screen_df			13
#define	WarningWaterHardnessScreen_df			14
#define	WarningProbeCalibrationScreen_df			15
#define	WarningProbeCalibration70Screen_df			16
#define	WarningProbeCalibrationRequiredValueScreen_df			17
#define	WarningProbeCalibrationRequiredValueRedScreen_df			18
#define	WarningProbeCalibrationRequiredValueImpossibleScreen_df			19
#define	WarningTooRapidChangeScreen_df			20
#define ParametersRequireValuepHScreen_df		21
#define ParametersRequireValueCLFScreen_df  22

/*Added by chau phuoc vu 14/11/2018*/
void DelayScreen_Decrement(void);
void DelayScreen(uint16_t time);
static uint16_t delayscreen = 0;
/* Exported constants ----------------------------------------------------------*/

#define DesignLabel01Color 					65535
#define DesignLabel02Color 					65535
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
/*Create Screen*/
void Create_StartScreen(void);
void Create_SettingsScreen(void);
/*Create DosingTest Screen*/
void Create_DosingTestStartStartScreen(void);
void Create_DosingTestStopStartScreen(void);
void Create_DosingTestStopStopScreen(void);
void Create_DosingTestStartStopScreen(void);
void Create_ParametersScreen(void);
void Create_ParametersPoolVolumeScreen(void);
void Create_ParametersFitrationPeriodScreen(void);
void Create_ParametersWaterScreen(void);
void Create_WarningMaximalSafetyScreen(void);
void Create_WarningExtremeConditionScreen(void);
void Create_WarningWaterHardnessScreen(void);
void Create_WarningProbeCalibration62_78Screen(void);
void Create_WarningProbeCalibrationScreen(void);
void Create_WarningProbeCalibration70Screen(void);
void Create_WarningProbeCalibrationRequiredValueScreen(void);
void Create_WarningProbeCalibrationRequiredValueRedScreen(void);
void Create_WarningProbeCalibrationRequiredValueImpossibleScreen(void);
void Create_WarningTooRapidChangeScreen(void);
void Create_ParametersRequireValuepHScreen(void);
void Create_ParametersRequireValueCLFScreen(void);

/*Show Screen*/
void Show_HomeScreen(void);
void Show_StartScreen(void);
void Show_SettingsScreen(void);
void Show_DosingTestStartStartScreen(void);
void Show_DosingTestStopStartScreen(void);
void Show_DosingTestStopStopScreen(void);
void Show_DosingTestStartStopScreen(void);
void Show_ParametersScreen(void);
void Show_ParametersPoolVolumeScreen(void);
void Show_ParametersFitrationPeriodScreen(void);
void Show_ParametersWaterScreen(void);
void Show_WarningMaximalSafetyScreen(void);
void Show_WarningExtremeConditionScreen(void);
void Show_WarningWaterHardnessScreen(void);
void Show_WarningProbeCalibration62_78Screen(void);
void Show_WarningProbeCalibrationScreen(void);
void Show_WarningProbeCalibration70Screen(void);
void Show_WarningProbeCalibrationRequiredValueScreen(void);
void Show_WarningProbeCalibrationrequiredValueRedScreen(void);
void Show_WarningProbeCalibrationRequiredValueImpossibleScreen(void);
void Show_WarningTooRapidChangeScreen(void);
void Show_ParametersRequireValuepHScreen(void);
void Show_ParametersRequireValueCLFScreen(void);

#ifdef __cplusplus
}
#endif

#endif /*__UIFRAMEWORK_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

