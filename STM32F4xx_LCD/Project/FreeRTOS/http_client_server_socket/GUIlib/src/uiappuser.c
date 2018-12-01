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
uint16_t PoolSelect;
uint16_t Temperature;
uint16_t WaterHardnessSelect;
uint16_t PoolVolume;
uint16_t FiltrationPeriod;
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
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_dec(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersPoolVolumeScreen_OK(void)
{
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
}
	///////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_dec(void)
{
}
	//////////////////////////////////////////////////////////////
void ParametersFitrationPeriodScreen_OK(void)
{
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
	SaveHalfWordDataToFlash();
	Show_ParametersScreen();
}
///////////////////////////////////////////////////////////////
void ParametersWaterScreen_BackToStart(void)
{
	DestroyPage(CurrentScreen);
	SaveHalfWordDataToFlash();
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
	Show_ParametersWaterScreen();
}


void WarningProbeCalibrationScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}

void WarningProbeCalibration70Screen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
}

void WarningProbeCalibrationRequiredValueScreen_OK(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersWaterScreen();
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
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_dec(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersRequireValuepHScreen_OK(void)
{
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
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_dec(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_OK(void)
{
}
//////////////////////////////////////////////////////////////
void ParametersRequireValueCLFScreen_pH(void)
{
	DestroyPage(CurrentScreen);
	Show_ParametersRequireValuepHScreen();
}

