/*******************************************************************************
* @file		: uiframework.c
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 26-Apr-2017
* @brief	: Screen Code
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
#include "float.h"
#include "LcdHal.h"
#include "TscHal.h"
#include "pictures.h"


GL_Page_TypeDef *CurrentScreen;
uint16_t		Screen = 0;

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup UI_Framework
  * @brief This file contains functions to configure the screens and controls
  * @{
  */

/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/

void Show_HomeScreen(void)
{
	Show_StartScreen();
}


/*Giao dien tu thiet ke*/
GL_Page_TypeDef StartScreen;
void Create_StartScreen(void)
{
	GL_PageControls_TypeDef* StartScreen_DesignButton02= NewRectControl(1,210,32,WHITE,StartScreen_Setting);
	Create_PageObj( &StartScreen ); 
	AddPageControlObj(250,240,StartScreen_DesignButton02,&StartScreen);
}
///////////////////////////////
void Show_StartScreen(void)
{
	UARTprintf("Create_StartScreen\r\n");
	Create_StartScreen();
	LCD_Clear(BLACK);
	/*VE CAC NUT DIEU KHIEN*/
	LCD_DrawFullRect(250,240,210,32,WHITE);//ve nut button
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,240,210,32,(uint8_t *)"SETTINGS");
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"CHAU PHUOC VU");
	LCD_DisplayStringLine(250,20,(uint8_t *)"BACH KHOA");
	LCD_DrawFullRect(20,60,210,160,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,160,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(80,30,(uint8_t *)"CHLORINE");
	LCD_DisplayStringLine(160,175,(uint8_t *)"mg/l");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(80,260,(uint8_t *)"PH--");
	LCD_DisplayStringLine(160,400,(uint8_t *)"pH");	
	StartScreen.ShowPage(&StartScreen,GL_TRUE);
	Screen = StartScreen_df;
	CurrentScreen = &StartScreen;
}
/*Giao dien tu thiet ke*/
GL_Page_TypeDef SettingsScreen;
void Create_SettingsScreen(void)
{
	GL_PageControls_TypeDef* SettingsDesignButton01= NewRectControl(1,210,30,WHITE,SettingsScreen_Language);
	GL_PageControls_TypeDef* SettingsDesignButton02= NewRectControl(2,210,30,WHITE,SettingsScreen_BackToStart);
	GL_PageControls_TypeDef* SettingsDesignButton03= NewRectControl(3,210,80,BLACK,SettingsScreen_Parameters);
	GL_PageControls_TypeDef* SettingsDesignButton04= NewRectControl(4,210,80,BLACK,SettingsScreen_Calibration);
	GL_PageControls_TypeDef* SettingsDesignButton05= NewRectControl(5,210,80,BLACK,SettingsScreen_DosingTest);
	GL_PageControls_TypeDef* SettingsDesignButton06= NewRectControl(6,210,80,BLACK,SettingsScreen_TypeOfProbe);
	Create_PageObj( &SettingsScreen ); 
	AddPageControlObj(250,240,SettingsDesignButton01,&SettingsScreen);
	AddPageControlObj(20,240,SettingsDesignButton02,&SettingsScreen);
	AddPageControlObj(20,60,SettingsDesignButton03,&SettingsScreen);
	AddPageControlObj(250,60,SettingsDesignButton04,&SettingsScreen);
	AddPageControlObj(20,150,SettingsDesignButton05,&SettingsScreen);
	AddPageControlObj(250,150,SettingsDesignButton06,&SettingsScreen);
	
}
////////////////////////////////////////
void Show_SettingsScreen(void)
{
	UARTprintf("Create_SettingsScreen\r\n");
	Create_SettingsScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,380,(uint8_t *)"SETTINGS");;
	LCD_DrawRect(20,60,80,210);
	LCD_DrawRect(250,60,80,210);
	LCD_DrawRect(20,150,80,210);
	LCD_DrawRect(250,150,80,210);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawRect(250,240,30,210);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(20,60,210,80,(uint8_t *)"PARAMETERS");
	LCD_DisplayStringLineInRect(250,60,210,80,(uint8_t *)"CALIBRATION");
	LCD_DisplayStringLineInRect(20,150,210,80,(uint8_t *)"DOSING TEST");
	LCD_DisplayStringLineInRect(250,150,210,80,(uint8_t *)"TYPE OF PROBE");
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"LANGUAGES");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	SettingsScreen.ShowPage(&SettingsScreen,GL_TRUE);
	Screen = SettingsScreen_df;
	CurrentScreen = &SettingsScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStartStartScreen;
void Create_DosingTestStartStartScreen(void)
{
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton01= NewRectControl(1,210,30,WHITE,DosingTestStartStartScreen_Back);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton02= NewRectControl(2,210,30,WHITE,DosingTestStartStartScreen_BackToStart);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton03= NewRectControl(3,210,60,VU_BLUE,DosingTestStartStartScreen_StartDisinf);
	GL_PageControls_TypeDef* DosingTestStartStartDesignButton04= NewRectControl(4,210,60,VU_YELLOW,DosingTestStartStartScreen_StartPh);
	Create_PageObj( &DosingTestStartStartScreen ); 
	AddPageControlObj(250,240,DosingTestStartStartDesignButton01,&DosingTestStartStartScreen);
	AddPageControlObj(20,240,DosingTestStartStartDesignButton02,&DosingTestStartStartScreen);
	AddPageControlObj(20,170,DosingTestStartStartDesignButton03,&DosingTestStartStartScreen);
	AddPageControlObj(250,170,DosingTestStartStartDesignButton04,&DosingTestStartStartScreen);	
}
////////////////////////////////////////
void Show_DosingTestStartStartScreen(void)
{
	UARTprintf("Create_DosingTestStartStartScreen\r\n");
	Create_DosingTestStartStartScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"START");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"START");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStartStartScreen.ShowPage(&DosingTestStartStartScreen,GL_TRUE);
	Screen = DosingTestStartStartScreen_df;
	CurrentScreen = &DosingTestStartStartScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStopStartScreen;
void Create_DosingTestStopStartScreen(void)
{	
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton01= NewRectControl(1,210,30,WHITE,DosingTestStopStartScreen_Back);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton02= NewRectControl(2,210,30,WHITE,DosingTestStopStartScreen_BackToStart);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton03= NewRectControl(3,210,60,VU_BLUE,DosingTestStopStartScreen_StopDisinf);
	GL_PageControls_TypeDef* DosingTestStopStartDesignButton04= NewRectControl(4,210,60,VU_YELLOW,DosingTestStopStartScreen_StartPh);
	Create_PageObj( &DosingTestStopStartScreen ); 
	AddPageControlObj(250,240,DosingTestStopStartDesignButton01,&DosingTestStopStartScreen);
	AddPageControlObj(20,240,DosingTestStopStartDesignButton02,&DosingTestStopStartScreen);
	AddPageControlObj(20,170,DosingTestStopStartDesignButton03,&DosingTestStopStartScreen);
	AddPageControlObj(250,170,DosingTestStopStartDesignButton04,&DosingTestStopStartScreen);	
}
////////////////////////////////////////
void Show_DosingTestStopStartScreen(void)
{
	UARTprintf("Create_DosingTestStopStartScreen\r\n");
	Create_DosingTestStopStartScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font16x24);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"STOP");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"START");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStopStartScreen.ShowPage(&DosingTestStopStartScreen,GL_TRUE);
	Screen = DosingTestStopStartScreen_df;
	CurrentScreen = &DosingTestStopStartScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStopStopScreen;
void Create_DosingTestStopStopScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,DosingTestStopStopScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,DosingTestStopStopScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,60,VU_BLUE,DosingTestStopStopScreen_StopDisinf);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,60,VU_YELLOW,DosingTestStopStopScreen_StopPh);
	Create_PageObj( &DosingTestStopStopScreen ); 
	AddPageControlObj(250,240,DesignButton01,&DosingTestStopStopScreen);
	AddPageControlObj(20,240,DesignButton02,&DosingTestStopStopScreen);
	AddPageControlObj(20,170,DesignButton03,&DosingTestStopStopScreen);
	AddPageControlObj(250,170,DesignButton04,&DosingTestStopStopScreen);	
}
////////////////////////////////////////
void Show_DosingTestStopStopScreen(void)
{
	UARTprintf("Create_DosingTestStopStopScreen\r\n");
	Create_DosingTestStopStopScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");	
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"STOP");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"STOP");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStopStopScreen.ShowPage(&DosingTestStopStopScreen,GL_TRUE);
	Screen = DosingTestStopStopScreen_df;
	CurrentScreen = &DosingTestStopStopScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef DosingTestStartStopScreen;
void Create_DosingTestStartStopScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,DosingTestStartStopScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,DosingTestStartStopScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,60,VU_BLUE,DosingTestStartStopScreen_StartDisinf);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,60,VU_YELLOW,DosingTestStartStopScreen_StopPh);
	Create_PageObj( &DosingTestStartStopScreen ); 
	AddPageControlObj(250,240,DesignButton01,&DosingTestStartStopScreen);
	AddPageControlObj(20,240,DesignButton02,&DosingTestStartStopScreen);
	AddPageControlObj(20,170,DesignButton03,&DosingTestStartStopScreen);
	AddPageControlObj(250,170,DesignButton04,&DosingTestStartStopScreen);
	
}
////////////////////////////////////////
void Show_DosingTestStartStopScreen(void)
{
	UARTprintf("Create_DosingTestStartStopScreen\r\n");
	Create_DosingTestStartStopScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,340,(uint8_t *)"DOSING TEST");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DISINF.");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");	
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,210);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,210,60,(uint8_t *)"START");
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"STOP");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	DosingTestStartStopScreen.ShowPage(&DosingTestStartStopScreen,GL_TRUE);
	Screen = DosingTestStartStopScreen_df;
	CurrentScreen = &DosingTestStartStopScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersScreen;
void Create_ParametersScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,210,80,BLACK,ParametersScreen_Pool);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,210,80,BLACK,ParametersScreen_Water);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,80,VU_BLUE,ParametersScreen_pH);
	Create_PageObj( &ParametersScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersScreen);
	AddPageControlObj(20,60,DesignButton03,&ParametersScreen);
	AddPageControlObj(250,60,DesignButton04,&ParametersScreen);
	AddPageControlObj(250,150,DesignButton05,&ParametersScreen);
	
}
////////////////////////////////////////
void Show_ParametersScreen(void)
{
	UARTprintf("Create_ParametersScreen\r\n");
	Create_ParametersScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,355,(uint8_t *)"PARAMETERS");
	LCD_DrawRect(20,60,80,210);
	LCD_DrawRect(250,60,80,210);
	LCD_DrawFullRect(20,150,210,80,VU_YELLOW);
	LCD_DrawFullRect(250,150,210,80,VU_BLUE);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_DisplayStringLineInRect(20,150,210,80,(uint8_t *)"DISINFECTION");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_DisplayStringLineInRect(250,150,210,80,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,60,210,80,(uint8_t *)"POOL");
	LCD_DisplayStringLineInRect(250,60,210,80,(uint8_t *)"WATER");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	LCD_SetColors(BLACK,WHITE);
	ParametersScreen.ShowPage(&ParametersScreen,GL_TRUE);
	Screen = ParametersScreen_df;
	CurrentScreen = &ParametersScreen;
}




/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersPoolVolumeScreen;
void Create_ParametersPoolVolumeScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersPoolVolumeScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersPoolVolumeScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,WHITE_BLACK,ParametersPoolVolumeScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,WHITE_BLACK,ParametersPoolVolumeScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,WHITE_BLACK,ParametersPoolVolumeScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersPoolVolumeScreen_FiltrationPeriod);
	Create_PageObj( &ParametersPoolVolumeScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersPoolVolumeScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersPoolVolumeScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersPoolVolumeScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersPoolVolumeScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersPoolVolumeScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersPoolVolumeScreen);	
}
////////////////////////////////////////
void Show_ParametersPoolVolumeScreen(void)
{
	UARTprintf("Create_ParametersVolumeScreen\r\n");
	Create_ParametersPoolVolumeScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"POOL PARAMETERS");
	LCD_DrawFullRect(20,60,210,100,VU_GRAY);
	LCD_DrawFullRect(250,60,210,100,VU_GRAY);
	LCD_SetBackColor(VU_GRAY);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"POOL VOLUME");
	LCD_DrawFullRect(95,140,60,20,BLACK);
	LCD_SetBackColor(VU_GRAY);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,255,(uint8_t *)"FILTRATION PERIOD");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(20,170,60,100);
	LCD_DrawRect(130,170,60,100);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,100,60,(uint8_t *)"+");
	LCD_DisplayStringLineInRect(130,170,100,60,(uint8_t *)"-");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"OK");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersPoolVolumeScreen.ShowPage(&ParametersPoolVolumeScreen,GL_TRUE);
	Screen = ParametersPoolVolumeScreen_df;
	CurrentScreen = &ParametersPoolVolumeScreen;
}



/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersFitrationPeriodScreen;
void Create_ParametersFitrationPeriodScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersFitrationPeriodScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersFitrationPeriodScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,WHITE_BLACK,ParametersFitrationPeriodScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,WHITE_BLACK,ParametersFitrationPeriodScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,WHITE_BLACK,ParametersFitrationPeriodScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersFitrationPeriodScreen_PoolVolume);
	Create_PageObj( &ParametersFitrationPeriodScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersFitrationPeriodScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersFitrationPeriodScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersFitrationPeriodScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersFitrationPeriodScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersFitrationPeriodScreen);
	AddPageControlObj(20,60,DesignButton06,&ParametersFitrationPeriodScreen);	
}
////////////////////////////////////////
void Show_ParametersFitrationPeriodScreen(void)
{
	UARTprintf("Create_ParametersFitrationPeriodScreen\r\n");
	Create_ParametersFitrationPeriodScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"POOL PARAMETERS");
	LCD_DrawFullRect(20,60,210,100,VU_GRAY);
	LCD_DrawFullRect(250,60,210,100,VU_GRAY);
	LCD_DrawFullRect(325,140,60,20,BLACK);
	LCD_SetColors(WHITE,VU_GRAY);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,30,(uint8_t *)"POOL VOLUME");
	LCD_SetColors(WHITE,VU_GRAY);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,255,(uint8_t *)"FILTRATION PERIOD");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(20,170,60,100);
	LCD_DrawRect(130,170,60,100);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,100,60,(uint8_t *)"+");
	LCD_DisplayStringLineInRect(130,170,100,60,(uint8_t *)"-");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"OK");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersFitrationPeriodScreen.ShowPage(&ParametersFitrationPeriodScreen,GL_TRUE);
	Screen = ParametersFitrationPeriodScreen_df;
	CurrentScreen = &ParametersFitrationPeriodScreen;
}




/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersWaterScreen;
void Create_ParametersWaterScreen(void)
{
	GL_RadioButtonGrp_TypeDef* Pool=NewRadioButtonGrp(1);
	GL_RadioButtonGrp_TypeDef* AverageWaterTemperature= NewRadioButtonGrp(2);
	GL_RadioButtonGrp_TypeDef* WaterHardness=NewRadioButtonGrp(3);
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(4,210,30,WHITE,ParametersWaterScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(5,210,30,WHITE,ParametersWaterScreen_BackToStart);
	GL_PageControls_TypeDef* CheckBoxIndoor= RADIO_BUTTON_ADD(Pool,(const uint8_t *)"",ParametersWaterScreen_Indoor);
	GL_PageControls_TypeDef* CheckBoxOutdoor= RADIO_BUTTON_ADD(Pool,(const uint8_t *)"",ParametersWaterScreen_Outdoor);
	GL_PageControls_TypeDef* CheckBoxExtremeConditions= RADIO_BUTTON_ADD(Pool,(const uint8_t *)"",ParametersWaterScreen_ExtremeCondition);
	GL_PageControls_TypeDef* CheckBoxLess20oC= RADIO_BUTTON_ADD(AverageWaterTemperature,(const uint8_t *)"",ParametersWaterScreen_Less20oC);
	GL_PageControls_TypeDef* CheckBox20oC_30oC= RADIO_BUTTON_ADD(AverageWaterTemperature,(const uint8_t *)"",ParametersWaterScreen_20oC_30oC);
	GL_PageControls_TypeDef* CheckBoxMore30oC= RADIO_BUTTON_ADD(AverageWaterTemperature,(const uint8_t *)"",ParametersWaterScreen_More30oC);
	GL_PageControls_TypeDef* CheckBoxSoft= RADIO_BUTTON_ADD(WaterHardness,(const uint8_t *)"",ParametersWaterScreen_Soft);
	GL_PageControls_TypeDef* CheckBoxHard= RADIO_BUTTON_ADD(WaterHardness,(const uint8_t *)"",ParametersWaterScreen_Hard);
	GL_PageControls_TypeDef* CheckBoxVeryHard= RADIO_BUTTON_ADD(WaterHardness,(const uint8_t *)"",ParametersWaterScreen_VeryHard);
	Create_PageObj( &ParametersWaterScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersWaterScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersWaterScreen);
	AddPageControlObj(270,85,CheckBoxIndoor,&ParametersWaterScreen);
	AddPageControlObj(340,85,CheckBoxOutdoor,&ParametersWaterScreen);
	AddPageControlObj(410,85,CheckBoxExtremeConditions,&ParametersWaterScreen);
	AddPageControlObj(270,140,CheckBoxLess20oC,&ParametersWaterScreen);	
	AddPageControlObj(340,140,CheckBox20oC_30oC,&ParametersWaterScreen);
	AddPageControlObj(410,140,CheckBoxMore30oC,&ParametersWaterScreen);
	AddPageControlObj(270,205,CheckBoxSoft,&ParametersWaterScreen);
	AddPageControlObj(340,205,CheckBoxHard,&ParametersWaterScreen);
	AddPageControlObj(410,205,CheckBoxVeryHard,&ParametersWaterScreen);
//  GL_RadioOption_TypeDef* pTmp = (GL_RadioOption_TypeDef*)(ParametersWaterScreen);
//	pTmp->IsChecked = GL_TRUE;
//	(Pool->RadioOptionCount) = 0;
	((GL_RadioOption_TypeDef*)(Pool->RadioOptions[PoolSelect]->objPTR))->IsChecked = GL_TRUE;
	((GL_RadioOption_TypeDef*)(AverageWaterTemperature->RadioOptions[Temperature]->objPTR))->IsChecked = GL_TRUE;
	((GL_RadioOption_TypeDef*)(WaterHardness->RadioOptions[WaterHardnessSelect]->objPTR))->IsChecked = GL_TRUE;
}
////////////////////////////////////////
void Show_ParametersWaterScreen(void)
{
	UARTprintf("Create_ParametersWaterScreen\r\n");
	Create_ParametersWaterScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,280,(uint8_t *)"WATER PARAMETERS");
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(55,30,(uint8_t *)"POOL");
	LCD_DisplayStringLine(120,30,(uint8_t *)"AVERAGE");
	LCD_DisplayStringLine(135,30,(uint8_t *)"WATER");
	LCD_DisplayStringLine(150,30,(uint8_t *)"TEMPERATURE");
	LCD_DisplayStringLine(185,30,(uint8_t *)"WATER");
	LCD_DisplayStringLine(200,30,(uint8_t *)"HARDNESS");
	LCD_SetFont(&Font8x8);
	LCD_DisplayStringLine(55,255,(uint8_t *)"indoor");
	LCD_DisplayStringLine(55,320,(uint8_t *)"outdoor");
	LCD_DisplayStringLine(120,255,(uint8_t *)"< 20oC");
	LCD_DisplayStringLine(120,320,(uint8_t *)"20-30oC");
	LCD_DisplayStringLine(120,395,(uint8_t *)"> 30oC");
	LCD_DisplayStringLine(185,265,(uint8_t *)"soft");
	LCD_DisplayStringLine(185,335,(uint8_t *)"hard");
	LCD_DisplayStringLine(185,385,(uint8_t *)"very hard");
	LCD_SetTextColor(BRIGHTRED);
	LCD_DisplayStringLine(55,390,(uint8_t *)"extreme");
	LCD_DisplayStringLine(70,385,(uint8_t *)"condition");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersWaterScreen.ShowPage(&ParametersWaterScreen,GL_TRUE);
	Screen = ParametersWaterScreen_df;
	CurrentScreen = &ParametersWaterScreen;
}




/*Warning Screen*/
GL_Page_TypeDef WarningMaximalSafetyScreen;
void Create_WarningMaximalSafetyScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_GREEN,WarningMaximalSafetyScreen_OK);
	Create_PageObj( &WarningMaximalSafetyScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningMaximalSafetyScreen);
}
////////////////////////////////////////
void Show_WarningMaximalSafetyScreen(void)
{
	UARTprintf("Show_WarningMaximalSafetyScreen\r\n");
	Create_WarningMaximalSafetyScreen();
	LCD_DrawFullRect(100,50,280,172,VU_GREEN);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"Maximal safety");
	LCD_DisplayStringLine(80,120,(uint8_t *)"disfection");
	LCD_DisplayStringLine(100,120,(uint8_t *)"dosage:");
	LCD_SetFont(&Font8x8);
	LCD_DisplayStringLine(150,230,(uint8_t *)"ml/m3");
	LCD_DisplayStringLine(160,230,(uint8_t *)"hour");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningMaximalSafetyScreen.ShowPage(&WarningMaximalSafetyScreen,GL_TRUE);
	Screen = WarningMaximalSafetyScreen_df;
	CurrentScreen = &WarningMaximalSafetyScreen;
}




/*Warning Screen*/
GL_Page_TypeDef WarningExtremeConditionScreen;
void Create_WarningExtremeConditionScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_GREEN,WarningExtremeConditionScreen_OK);
	Create_PageObj( &WarningExtremeConditionScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningExtremeConditionScreen);
}
////////////////////////////////////////
void Show_WarningExtremeConditionScreen(void)
{
	UARTprintf("Show_WarningExtremeConditionScreen\r\n");
	Create_WarningExtremeConditionScreen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"Extreme condition");
	LCD_DisplayStringLine(80,120,(uint8_t *)"maximal safety");
	LCD_DisplayStringLine(100,120,(uint8_t *)"dosage:");
	LCD_SetFont(&Font8x8);
	LCD_DisplayStringLine(150,230,(uint8_t *)"ml/m3");
	LCD_DisplayStringLine(160,230,(uint8_t *)"hour");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningExtremeConditionScreen.ShowPage(&WarningExtremeConditionScreen,GL_TRUE);
	Screen = WarningExtremeConditionScreen_df;
	CurrentScreen = &WarningExtremeConditionScreen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningWaterHardnessScreen;
void Create_WarningWaterHardnessScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_GREEN,WarningExtremeConditionScreen_OK);
	Create_PageObj( &WarningWaterHardnessScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningWaterHardnessScreen);
}
////////////////////////////////////////
void Show_WarningWaterHardnessScreen(void)
{
	UARTprintf("Show_WarningWaterHardnessScreen\r\n");
	Create_WarningWaterHardnessScreen();
	LCD_DrawFullRect(100,50,280,172,VU_GREEN);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"Water hardness");
	LCD_DisplayStringLine(90,120,(uint8_t *)"Soft to moderately hard <9 odH");
	LCD_DisplayStringLine(110,120,(uint8_t *)"If pH value does not change");
	LCD_DisplayStringLine(130,120,(uint8_t *)"Bach Khoa stops after 10 doses.");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningWaterHardnessScreen.ShowPage(&WarningWaterHardnessScreen,GL_TRUE);
	Screen = WarningWaterHardnessScreen_df;
	CurrentScreen = &WarningWaterHardnessScreen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibration62_78Screen;
void Create_WarningProbeCalibration62_78Screen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_RED,WarningProbeCalibration62_78Screen_OK);
	Create_PageObj( &WarningProbeCalibration62_78Screen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibration62_78Screen);
}
////////////////////////////////////////
void Show_WarningProbeCalibration62_78Screen(void)
{
	UARTprintf("Show_WarningProbeCalibration62_78Screen\r\n");
	Create_WarningProbeCalibration62_78Screen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"Probe cannot be calibrate!");
	LCD_DisplayStringLine(120,120,(uint8_t *)"You are calibrating outside the");
	LCD_DisplayStringLine(140,120,(uint8_t *)"range of 6.2 - 7.8!");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_RED);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibration62_78Screen.ShowPage(&WarningProbeCalibration62_78Screen,GL_TRUE);
	Screen = WarningProbeCalibration62_78Screen_df;
	CurrentScreen = &WarningProbeCalibration62_78Screen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibrationScreen;
void Create_WarningProbeCalibrationScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_RED,WarningProbeCalibrationScreen_OK);
	Create_PageObj( &WarningProbeCalibrationScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibrationScreen);
}
////////////////////////////////////////
void Show_WarningProbeCalibrationScreen(void)
{
	UARTprintf("Show_WarningProbeCalibrationScreen\r\n");
	Create_WarningProbeCalibrationScreen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"Probe cannot be calibrate!");
	LCD_DisplayStringLine(120,120,(uint8_t *)"We are recommended replacing");
	LCD_DisplayStringLine(140,120,(uint8_t *)"the probe with a new one.");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_RED);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibrationScreen.ShowPage(&WarningProbeCalibrationScreen,GL_TRUE);
	Screen = WarningProbeCalibrationScreen_df;
	CurrentScreen = &WarningProbeCalibrationScreen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibration70Screen;
void Create_WarningProbeCalibration70Screen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_GREEN,WarningProbeCalibration70Screen_OK);
	Create_PageObj( &WarningProbeCalibration70Screen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibration70Screen);
}
////////////////////////////////////////
void Show_WarningProbeCalibration70Screen(void)
{
	UARTprintf("Show_WarningProbeCalibration70Screen\r\n");
	Create_WarningProbeCalibration70Screen();
	LCD_DrawFullRect(100,50,280,172,VU_GREEN);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"Calibration recommended by");
	LCD_DisplayStringLine(110,120,(uint8_t *)"using buffer pH 7,0.");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibration70Screen.ShowPage(&WarningProbeCalibration70Screen,GL_TRUE);
	Screen = WarningProbeCalibration70Screen_df;
	CurrentScreen = &WarningProbeCalibration70Screen;
}




/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibrationRequiredValueScreen;
void Create_WarningProbeCalibrationRequiredValueScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_GREEN,WarningProbeCalibrationRequiredValueScreen_OK);
	Create_PageObj( &WarningProbeCalibrationRequiredValueScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibrationRequiredValueScreen);
}
////////////////////////////////////////
void Show_WarningProbeCalibrationRequiredValueScreen(void)
{
	UARTprintf("Show_WarningProbeCalibrationRequiredValueScreen\r\n");
	Create_WarningProbeCalibrationRequiredValueScreen();
	LCD_DrawFullRect(100,50,280,172,VU_GREEN);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"The chlorine content in pool");
	LCD_DisplayStringLine(110,120,(uint8_t *)"water must be greater than");
	LCD_DisplayStringLine(130,120,(uint8_t *)"\"required value\".");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_GREEN);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibrationRequiredValueScreen.ShowPage(&WarningProbeCalibrationRequiredValueScreen,GL_TRUE);
	Screen = WarningProbeCalibrationRequiredValueScreen_df;
	CurrentScreen = &WarningProbeCalibrationRequiredValueScreen;
}




/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibrationRequiredValueRedScreen;
void Create_WarningProbeCalibrationRequiredValueRedScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_RED,WarningProbeCalibrationRequiredValueRedScreen_OK);
	Create_PageObj( &WarningProbeCalibrationRequiredValueRedScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibrationRequiredValueRedScreen);
}
////////////////////////////////////////
void Show_WarningProbeCalibrationrequiredValueRedScreen(void)
{
	UARTprintf("Show_WarningProbeCalibrationRequiredValueRedScreen\r\n");
	Create_WarningProbeCalibrationRequiredValueRedScreen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"The chlorine content in pool");
	LCD_DisplayStringLine(110,120,(uint8_t *)"water must be greater than");
	LCD_DisplayStringLine(130,120,(uint8_t *)"\"required value\".");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_RED);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibrationRequiredValueRedScreen.ShowPage(&WarningProbeCalibrationRequiredValueRedScreen,GL_TRUE);
	Screen = WarningProbeCalibrationRequiredValueRedScreen_df;
	CurrentScreen = &WarningProbeCalibrationRequiredValueRedScreen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningProbeCalibrationRequiredValueImpossibleScreen;
void Create_WarningProbeCalibrationRequiredValueImpossibleScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,60,30,VU_RED,WarningProbeCalibrationRequiredValueImpossibleScreen_OK);
	Create_PageObj( &WarningProbeCalibrationRequiredValueImpossibleScreen ); 
	AddPageControlObj(300,170,DesignButton01,&WarningProbeCalibrationRequiredValueImpossibleScreen);
}
////////////////////////////////////////
void Show_WarningProbeCalibrationRequiredValueImpossibleScreen(void)
{
	UARTprintf("Show_WarningProbeCalibrationRequiredValueImpossibleScreen\r\n");
	Create_WarningProbeCalibrationRequiredValueImpossibleScreen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"PROBE CALIBRATION");
	LCD_DisplayStringLine(90,120,(uint8_t *)"Calibration is impossible!");
	LCD_DisplayStringLine(110,120,(uint8_t *)"Probe sensitivity too low.");
	LCD_DisplayStringLine(130,120,(uint8_t *)"Change:");
	LCD_DisplayStringLine(150,120,(uint8_t *)"electrolyte/membrane/probe.");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(300,170,30,60);
	LCD_SetColors(WHITE,VU_RED);
	LCD_DisplayStringLineInRect(300,170,60,30,(uint8_t *)"OK");
	WarningProbeCalibrationRequiredValueImpossibleScreen.ShowPage(&WarningProbeCalibrationRequiredValueImpossibleScreen,GL_TRUE);
	Screen = WarningProbeCalibrationRequiredValueImpossibleScreen_df;
	CurrentScreen = &WarningProbeCalibrationRequiredValueImpossibleScreen;
}



/*Warning Screen*/
GL_Page_TypeDef WarningTooRapidChangeScreen;
void Create_WarningTooRapidChangeScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,200,30,VU_RED,WarningTooRapidChangeScreen_CancelRestictions);
	Create_PageObj( &WarningTooRapidChangeScreen ); 
	AddPageControlObj(160,170,DesignButton01,&WarningTooRapidChangeScreen);
}
////////////////////////////////////////
void Show_WarningTooRapidChangeScreen(void)
{
	UARTprintf("Show_WarningTooRapidChangeScreen\r\n");
	Create_WarningTooRapidChangeScreen();
	LCD_DrawFullRect(100,50,280,172,VU_RED);
	LCD_SetColors(WHITE,VU_RED);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(60,120,(uint8_t *)"Too rapid change of pH value.");
	LCD_DisplayStringLine(90,120,(uint8_t *)"BACH KHOA stop regulations of");
	LCD_DisplayStringLine(110,120,(uint8_t *)"pH for 2 hours for safety");
	LCD_DisplayStringLine(130,120,(uint8_t *)"reasons.");
	LCD_SetTextColor(WHITE);
	LCD_DrawRect(160,170,30,200);
	LCD_SetColors(WHITE,VU_RED);
	LCD_DisplayStringLineInRect(160,170,200,30,(uint8_t *)"CANCEL RESTRICTIONS");
	WarningTooRapidChangeScreen.ShowPage(&WarningTooRapidChangeScreen,GL_TRUE);
	Screen = WarningTooRapidChangeScreen_df;
	CurrentScreen = &WarningTooRapidChangeScreen;
}




/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValuepHScreen;
void Create_ParametersRequireValuepHScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValuepHScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValuepHScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,BLUE_BLACK,ParametersRequireValuepHScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,BLUE_BLACK,ParametersRequireValuepHScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,BLUE_BLACK,ParametersRequireValuepHScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValuepHScreen_CLF);
	Create_PageObj( &ParametersRequireValuepHScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValuepHScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValuepHScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValuepHScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValuepHScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValuepHScreen);
	AddPageControlObj(20,60,DesignButton06,&ParametersRequireValuepHScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValuepHScreen(void)
{
	UARTprintf("Show_ParametersRequireValuepHScreen\r\n");
	Create_ParametersRequireValuepHScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"REQUIRED VALUES");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetBackColor(VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(70,30,(uint8_t *)"CLF");
	LCD_SetBackColor(VU_BLUE);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DrawFullRect(325,140,60,20,BLACK);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_BLUE);
	LCD_DrawRect(20,170,60,100);
	LCD_DrawRect(130,170,60,100);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,100,60,(uint8_t *)"+");
	LCD_DisplayStringLineInRect(130,170,100,60,(uint8_t *)"-");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"OK");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersRequireValuepHScreen.ShowPage(&ParametersRequireValuepHScreen,GL_TRUE);
	Screen = ParametersRequireValuepHScreen_df;
	CurrentScreen = &ParametersRequireValuepHScreen;
}




/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueCLFScreen;
void Create_ParametersRequireValueCLFScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueCLFScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueCLFScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,YELLOW_BLACK,ParametersRequireValueCLFScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,YELLOW_BLACK,ParametersRequireValueCLFScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,YELLOW_BLACK,ParametersRequireValueCLFScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueCLFScreen_pH);
	Create_PageObj( &ParametersRequireValueCLFScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueCLFScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueCLFScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueCLFScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueCLFScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueCLFScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersRequireValueCLFScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueCLFScreen(void)
{
	UARTprintf("Show_ParametersRequireValueCLFScreen\r\n");
	Create_ParametersRequireValueCLFScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"REQUIRED VALUES");
	LCD_DrawFullRect(20,60,210,100,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetBackColor(VU_YELLOW);
	LCD_SetFont(&Font16x24);
	LCD_DisplayStringLine(70,30,(uint8_t *)"CLF");
	LCD_DrawFullRect(95,140,60,20,BLACK);
	LCD_SetBackColor(VU_BLUE);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_YELLOW);
	LCD_DrawRect(20,170,60,100);
	LCD_DrawRect(130,170,60,100);
	LCD_DrawRect(250,170,60,210);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,170,100,60,(uint8_t *)"+");
	LCD_DisplayStringLineInRect(130,170,100,60,(uint8_t *)"-");
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(250,170,210,60,(uint8_t *)"OK");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(BLACK,WHITE);
	ParametersRequireValueCLFScreen.ShowPage(&ParametersRequireValueCLFScreen,GL_TRUE);
	Screen = ParametersRequireValueCLFScreen_df;
	CurrentScreen = &ParametersRequireValueCLFScreen;
}

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 
/*Added by chau phuoc vu 14/11/2018*/
void DelayScreen_Decrement(void)
{
	if (delayscreen != 0)
		delayscreen--;
	else ;
}
void DelayScreen(uint16_t time)
{
	delayscreen = time;
	while(delayscreen != 0);
}
