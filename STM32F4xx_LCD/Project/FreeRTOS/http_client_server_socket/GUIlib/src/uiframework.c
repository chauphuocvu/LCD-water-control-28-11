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
	LCD_DrawFullRect(250,60,210,160,VU_BLUE);
// chon man hinh startscreen theo cai dat tu type of probe
	switch(TypeofProbe)
	{
		case FREECHLORINE:
				LCD_DrawFullRect(20,60,210,160,VU_YELLOW);
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,30,(uint8_t *)"CHLORINE");
				LCD_DisplayStringLine(160,175,(uint8_t *)"mg/l");
			break;
		case REDOXPROBE:
				LCD_DrawFullRect(20,60,210,160,VU_YELLOW);
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,30,(uint8_t *)"REDOX");
				LCD_DisplayStringLine(160,175,(uint8_t *)"mV");
			break;
		case MLPERHOUR:
				LCD_DrawFullRect(20,60,210,160,VU_YELLOW);
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,30,(uint8_t *)"DOSE");
				LCD_DisplayAdjStringLine(80,130,(uint8_t *)"ml/m3hour",LCD_FALSE);
			break;
		case MLPERDAY:
				LCD_DrawFullRect(20,60,210,160,VU_GRAY);
				LCD_SetColors(BLACK,VU_GRAY);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,30,(uint8_t *)"DOSE");
				LCD_DisplayStringLine(80,130,(uint8_t *)"ml/m3day");
			break;
		default:
			break;
	}
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
	GL_PageControls_TypeDef* SettingsDesignButton01= NewRectControl(1,130,30,WHITE_BLACK,SettingsScreen_Language);
	GL_PageControls_TypeDef* SettingsDesignButton02= NewRectControl(2,160,30,WHITE,SettingsScreen_BackToStart);
	GL_PageControls_TypeDef* SettingsDesignButton03= NewRectControl(3,210,80,BLACK,SettingsScreen_Parameters);
	GL_PageControls_TypeDef* SettingsDesignButton04= NewRectControl(4,210,80,BLACK,SettingsScreen_Calibration);
	GL_PageControls_TypeDef* SettingsDesignButton05= NewRectControl(5,210,80,BLACK,SettingsScreen_DosingTest);
	GL_PageControls_TypeDef* SettingsDesignButton06= NewRectControl(6,210,80,BLACK,SettingsScreen_TypeOfProbe);
	GL_PageControls_TypeDef* SettingsDesignButton07= NewRectControl(7,130,30,WHITE_BLACK,SettingsScreen_SaveData);
	Create_PageObj( &SettingsScreen ); 
	AddPageControlObj(330,240,SettingsDesignButton01,&SettingsScreen);
	AddPageControlObj(20,240,SettingsDesignButton02,&SettingsScreen);
	AddPageControlObj(20,60,SettingsDesignButton03,&SettingsScreen);
	AddPageControlObj(250,60,SettingsDesignButton04,&SettingsScreen);
	AddPageControlObj(20,150,SettingsDesignButton05,&SettingsScreen);
	AddPageControlObj(250,150,SettingsDesignButton06,&SettingsScreen);
	AddPageControlObj(190,240,SettingsDesignButton07,&SettingsScreen);
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
	LCD_DrawFullRect(20,240,160,30,WHITE);
	LCD_DrawRect(190,240,30,130);
	LCD_DrawRect(330,240,30,130);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLineInRect(20,60,210,80,(uint8_t *)"PARAMETERS");
	LCD_DisplayStringLineInRect(250,60,210,80,(uint8_t *)"CALIBRATION");
	LCD_DisplayStringLineInRect(20,150,210,80,(uint8_t *)"DOSING TEST");
	LCD_DisplayStringLineInRect(250,150,210,80,(uint8_t *)"TYPE OF PROBE");
	LCD_DisplayStringLineInRect(190,240,130,30,(uint8_t *)"SAVE DATA");
	LCD_DisplayStringLineInRect(330,240,130,30,(uint8_t *)"LANGUAGES");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(20,240,160,30,(uint8_t *)"BACK TO START");
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
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,80,NONE,ParametersScreen_pH);
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
	LCD_DisplayStringLine(65,30,(uint8_t *)"POOL");
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
	CurrentScreen = &WarningMaximalSafetyScreen;
	Screen = WarningMaximalSafetyScreen_df;
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
	CurrentScreen = &WarningExtremeConditionScreen;
	Screen = WarningExtremeConditionScreen_df;
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
	CurrentScreen = &WarningWaterHardnessScreen;
	Screen = WarningWaterHardnessScreen_df;
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
	CurrentScreen = &WarningProbeCalibration62_78Screen;
	Screen = WarningProbeCalibration62_78Screen_df;
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
	CurrentScreen = &WarningProbeCalibrationScreen;
	Screen = WarningProbeCalibrationScreen_df;
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
	CurrentScreen = &WarningProbeCalibration70Screen;
	Screen = WarningProbeCalibration70Screen_df;
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
	CurrentScreen = &WarningProbeCalibrationRequiredValueScreen;
	Screen = WarningProbeCalibrationRequiredValueScreen_df;
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
	CurrentScreen = &WarningProbeCalibrationRequiredValueRedScreen;
	Screen = WarningProbeCalibrationRequiredValueRedScreen_df;
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
	CurrentScreen = &WarningProbeCalibrationRequiredValueImpossibleScreen;
	Screen = WarningProbeCalibrationRequiredValueImpossibleScreen_df;
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
	CurrentScreen = &WarningTooRapidChangeScreen;
	Screen = WarningTooRapidChangeScreen_df;
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
	LCD_SetTextColor(BLACK);
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
	LCD_SetTextColor(BLACK);
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


/*Giao dien tu thiet ke*/
GL_Page_TypeDef CalibrationScreen;
void Create_CalibrationScreen(void)
{
	GL_PageControls_TypeDef* SettingsDesignButton01= NewRectControl(1,210,30,WHITE,CalibrationScreen_Back);
	GL_PageControls_TypeDef* SettingsDesignButton02= NewRectControl(2,210,30,WHITE,CalibrationScreen_BackToStart);
	GL_PageControls_TypeDef* SettingsDesignButton03= NewRectControl(3,210,80,NONE,CalibrationScreen_CLFProbe);
	GL_PageControls_TypeDef* SettingsDesignButton04= NewRectControl(4,210,80,NONE,CalibrationScreen_pHProbe);
	GL_PageControls_TypeDef* SettingsDesignButton05= NewRectControl(5,210,80,BLACK,CalibrationScreen_WaterThermometer);
	GL_PageControls_TypeDef* SettingsDesignButton06= NewRectControl(6,210,80,BLACK,CalibrationScreen_AirThermometer);
	Create_PageObj( &CalibrationScreen ); 
	AddPageControlObj(250,240,SettingsDesignButton01,&CalibrationScreen);
	AddPageControlObj(20,240,SettingsDesignButton02,&CalibrationScreen);
	AddPageControlObj(20,60,SettingsDesignButton03,&CalibrationScreen);
	AddPageControlObj(250,60,SettingsDesignButton04,&CalibrationScreen);
	AddPageControlObj(20,150,SettingsDesignButton05,&CalibrationScreen);
	AddPageControlObj(250,150,SettingsDesignButton06,&CalibrationScreen);
	
}
////////////////////////////////////////
void Show_CalibrationScreen(void)
{
	UARTprintf("Create_CalibrationScreen\r\n");
	Create_CalibrationScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,345,(uint8_t *)"CALIBRATION");;
	LCD_DrawFullRect(20,60,210,80,VU_YELLOW);
	LCD_DrawFullRect(250,60,210,80,VU_BLUE);
	LCD_DrawRect(20,150,80,210);
	LCD_DrawRect(250,150,80,210);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetFont(&Font12x12);
	LCD_SetColors(BLACK,VU_YELLOW);
	LCD_DisplayStringLineInRect(20,60,210,50,(uint8_t *)"CLF PROBE");
	LCD_DisplayStringLineInRect(20,85,210,50,(uint8_t *)"CALIBRATION");
	LCD_SetColors(BLACK,VU_BLUE);
	LCD_DisplayStringLineInRect(250,60,210,50,(uint8_t *)"pH PROBE");
	LCD_DisplayStringLineInRect(250,85,210,50,(uint8_t *)"CALIBRATION");
	LCD_SetColors(WHITE,BLACK);
	LCD_DisplayStringLineInRect(20,150,210,50,(uint8_t *)"WATER");
	LCD_DisplayStringLineInRect(20,175,210,50,(uint8_t *)"THERMOMETER");
	LCD_DisplayStringLineInRect(250,150,210,50,(uint8_t *)"AIR");
	LCD_DisplayStringLineInRect(250,175,210,50,(uint8_t *)"THERMOMETER");
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");
	CalibrationScreen.ShowPage(&CalibrationScreen,GL_TRUE);
	Screen = CalibrationScreen_df;
	CurrentScreen = &CalibrationScreen;
}









/*Giao dien tu thiet ke*/
GL_Page_TypeDef CalibrationpHProbeScreen;
void Create_CalibrationpHProbeScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,CalibrationpHProbeScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,CalibrationpHProbeScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,BLUE_BLACK,CalibrationpHProbeScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,BLUE_BLACK,CalibrationpHProbeScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,BLUE_BLACK,CalibrationpHProbeScreen_OK);
	Create_PageObj( &CalibrationpHProbeScreen ); 
	AddPageControlObj(250,240,DesignButton01,&CalibrationpHProbeScreen);
	AddPageControlObj(20,240,DesignButton02,&CalibrationpHProbeScreen);
	AddPageControlObj(20,170,DesignButton03,&CalibrationpHProbeScreen);
	AddPageControlObj(130,170,DesignButton04,&CalibrationpHProbeScreen);
	AddPageControlObj(250,170,DesignButton05,&CalibrationpHProbeScreen);
}
////////////////////////////////////////
void Show_CalibrationpHProbeScreen(void)
{
	UARTprintf("Show_CalibrationpHProbeScreen\r\n");
	Create_CalibrationpHProbeScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,230,(uint8_t *)"pH CALIBRATION PROBE");
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,30,(uint8_t *)"Calibration");
	LCD_DisplayStringLine(90,30,(uint8_t *)"recommended by");
	LCD_DisplayStringLine(110,30,(uint8_t *)"using buffer pH 7,0.");
	LCD_SetBackColor(VU_BLUE);
	LCD_SetTextColor(BLACK);
	LCD_SetFont(&Font12x12);
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
	CalibrationpHProbeScreen.ShowPage(&CalibrationpHProbeScreen,GL_TRUE);
	Screen = CalibrationpHProbeScreen_df;
	CurrentScreen = &CalibrationpHProbeScreen;
}







/*Giao dien tu thiet ke*/
GL_Page_TypeDef CalibrationCLFProbeScreen;
void Create_CalibrationCLFProbeScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,CalibrationCLFProbeScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,CalibrationCLFProbeScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,YELLOW_BLACK,CalibrationCLFProbeScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,YELLOW_BLACK,CalibrationCLFProbeScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,YELLOW_BLACK,CalibrationCLFProbeScreen_OK);
	Create_PageObj( &CalibrationCLFProbeScreen ); 
	AddPageControlObj(250,240,DesignButton01,&CalibrationCLFProbeScreen);
	AddPageControlObj(20,240,DesignButton02,&CalibrationCLFProbeScreen);
	AddPageControlObj(20,170,DesignButton03,&CalibrationCLFProbeScreen);
	AddPageControlObj(130,170,DesignButton04,&CalibrationCLFProbeScreen);
	AddPageControlObj(250,170,DesignButton05,&CalibrationCLFProbeScreen);
}
////////////////////////////////////////
void Show_CalibrationCLFProbeScreen(void)
{
	UARTprintf("Show_CalibrationCLFProbeScreen\r\n");
	Create_CalibrationCLFProbeScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,215,(uint8_t *)"CLF CALIBRATION PROBE");
	LCD_DrawFullRect(250,60,210,100,VU_YELLOW);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,30,(uint8_t *)"The chlorine content in");
	LCD_DisplayStringLine(90,30,(uint8_t *)"pool water must be greater");
	LCD_DisplayStringLine(110,30,(uint8_t *)"than \"required value\".");
	LCD_SetBackColor(VU_YELLOW);
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,260,(uint8_t *)"CLF");
	LCD_DrawFullRect(325,140,60,20,BLACK);
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
	CalibrationCLFProbeScreen.ShowPage(&CalibrationCLFProbeScreen,GL_TRUE);
	Screen = CalibrationCLFProbeScreen_df;
	CurrentScreen = &CalibrationCLFProbeScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueRedoxpH_RedoxScreen;
void Create_ParametersRequireValueRedoxpH_RodexScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueRedoxpH_RedoxScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueRedoxpH_RedoxScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,YELLOW_BLACK,ParametersRequireValueRedoxpH_RedoxScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,YELLOW_BLACK,ParametersRequireValueRedoxpH_RedoxScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,YELLOW_BLACK,ParametersRequireValueRedoxpH_RedoxScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueRedoxpH_RedoxScreen_pH);
	Create_PageObj( &ParametersRequireValueRedoxpH_RedoxScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueRedoxpH_RedoxScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueRedoxpH_RedoxScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueRedoxpH_RedoxScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueRedoxpH_RedoxScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueRedoxpH_RedoxScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersRequireValueRedoxpH_RedoxScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueRedoxpH_RodexScreen(void)
{
	UARTprintf("Show_ParametersRequireValueRedoxpH_RodexScreen\r\n");
	Create_ParametersRequireValueRedoxpH_RodexScreen();
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
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"REDOX");
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
	ParametersRequireValueRedoxpH_RedoxScreen.ShowPage(&ParametersRequireValueRedoxpH_RedoxScreen,GL_TRUE);
	Screen = ParametersRequireValueRedoxpH_RedoxScreen_df;
	CurrentScreen = &ParametersRequireValueRedoxpH_RedoxScreen;
}


/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueRedoxpH_pHScreen;
void Create_ParametersRequireValueRedoxpH_pHScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueRedoxpH_pHScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueRedoxpH_pHScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,BLUE_BLACK,ParametersRequireValueRedoxpH_pHScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,BLUE_BLACK,ParametersRequireValueRedoxpH_pHScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,BLUE_BLACK,ParametersRequireValueRedoxpH_pHScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueRedoxpH_pHScreen_Rodex);
	Create_PageObj( &ParametersRequireValueRedoxpH_pHScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueRedoxpH_pHScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueRedoxpH_pHScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueRedoxpH_pHScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueRedoxpH_pHScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueRedoxpH_pHScreen);
	AddPageControlObj(20,60,DesignButton06,&ParametersRequireValueRedoxpH_pHScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueRedoxpH_pHScreen(void)
{
	UARTprintf("Show_ParametersRequireValueRedoxpH_pHScreen\r\n");
	Create_ParametersRequireValueRedoxpH_pHScreen();
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
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"REDOX");
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
	ParametersRequireValueRedoxpH_pHScreen.ShowPage(&ParametersRequireValueRedoxpH_pHScreen,GL_TRUE);
	Screen = ParametersRequireValueRedoxpH_pHScreen_df;
	CurrentScreen = &ParametersRequireValueRedoxpH_pHScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueDosepH_DoseHourScreen;
void Create_ParametersRequireValueDosepH_DoseHourScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueDosepH_DoseHourScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueDosepH_DoseHourScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,YELLOW_BLACK,ParametersRequireValueDosepH_DoseHourScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,YELLOW_BLACK,ParametersRequireValueDosepH_DoseHourScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,YELLOW_BLACK,ParametersRequireValueDosepH_DoseHourScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueDosepH_DoseHourScreen_pH);
	Create_PageObj( &ParametersRequireValueDosepH_DoseHourScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueDosepH_DoseHourScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueDosepH_DoseHourScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueDosepH_DoseHourScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueDosepH_DoseHourScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueDosepH_DoseHourScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersRequireValueDosepH_DoseHourScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueDosepH_DoseHourScreen(void)
{
	UARTprintf("Show_ParametersRequireValueDosepH_DoseHourScreen\r\n");
	Create_ParametersRequireValueDosepH_DoseHourScreen();
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
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DOSE");
	LCD_DisplayStringLine(70,120,(uint8_t *)"ml/m3hour");
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
	ParametersRequireValueDosepH_DoseHourScreen.ShowPage(&ParametersRequireValueDosepH_DoseHourScreen,GL_TRUE);
	Screen = ParametersRequireValueDosepH_DoseHourScreen_df;
	CurrentScreen = &ParametersRequireValueDosepH_DoseHourScreen;
}





/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueDosepH_DoseHour_pHScreen;
void Create_ParametersRequireValueDosepH_DoseHour_pHScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueDosepH_DoseHour_pHScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueDosepH_DoseHour_pHScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseHour_pHScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseHour_pHScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseHour_pHScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueDosepH_DoseHour_pHScreen_Dose);
	Create_PageObj( &ParametersRequireValueDosepH_DoseHour_pHScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueDosepH_DoseHour_pHScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueDosepH_DoseHour_pHScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueDosepH_DoseHour_pHScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueDosepH_DoseHour_pHScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueDosepH_DoseHour_pHScreen);
	AddPageControlObj(20,60,DesignButton06,&ParametersRequireValueDosepH_DoseHour_pHScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueDosepH_DoseHour_pHScreen(void)
{
	UARTprintf("Show_ParametersRequireValueDosepH_DoseHour_pHScreen\r\n");
	Create_ParametersRequireValueDosepH_DoseHour_pHScreen();
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
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DOSE");
	LCD_DisplayStringLine(70,120,(uint8_t *)"ml/m3hour");
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
	ParametersRequireValueDosepH_DoseHour_pHScreen.ShowPage(&ParametersRequireValueDosepH_DoseHour_pHScreen,GL_TRUE);
	Screen = ParametersRequireValueDosepH_DoseHour_pHScreen_df;
	CurrentScreen = &ParametersRequireValueDosepH_DoseHour_pHScreen;
}





/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueDosepH_DoseDayScreen;
void Create_ParametersRequireValueDosepH_DoseDayScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueDosepH_DoseDayScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueDosepH_DoseDayScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,GRAY_BLACK,ParametersRequireValueDosepH_DoseDayScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,GRAY_BLACK,ParametersRequireValueDosepH_DoseDayScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,GRAY_BLACK,ParametersRequireValueDosepH_DoseDayScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueDosepH_DoseDayScreen_pH);
	Create_PageObj( &ParametersRequireValueDosepH_DoseDayScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueDosepH_DoseDayScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueDosepH_DoseDayScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueDosepH_DoseDayScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueDosepH_DoseDayScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueDosepH_DoseDayScreen);
	AddPageControlObj(250,60,DesignButton06,&ParametersRequireValueDosepH_DoseDayScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueDosepH_DoseDayScreen(void)
{
	UARTprintf("Show_ParametersRequireValueDosepH_DoseDayScreen\r\n");
	Create_ParametersRequireValueDosepH_DoseDayScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"REQUIRED VALUES");
	LCD_DrawFullRect(20,60,210,100,VU_GRAY);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetBackColor(VU_GRAY);
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DOSE");
	LCD_DisplayStringLine(70,130,(uint8_t *)"ml/m3day");
	LCD_DrawFullRect(95,140,60,20,BLACK);
	LCD_SetBackColor(VU_BLUE);
	LCD_DisplayStringLine(70,260,(uint8_t *)"pH");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_GRAY);
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
	ParametersRequireValueDosepH_DoseDayScreen.ShowPage(&ParametersRequireValueDosepH_DoseDayScreen,GL_TRUE);
	Screen = ParametersRequireValueDosepH_DoseDayScreen_df;
	CurrentScreen = &ParametersRequireValueDosepH_DoseDayScreen;

}





/*Giao dien tu thiet ke*/
GL_Page_TypeDef ParametersRequireValueDosepH_DoseDay_pHScreen;
void Create_ParametersRequireValueDosepH_DoseDay_pHScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,ParametersRequireValueDosepH_DoseDay_pHScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,ParametersRequireValueDosepH_DoseDay_pHScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseDay_pHScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseDay_pHScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,BLUE_BLACK,ParametersRequireValueDosepH_DoseDay_pHScreen_OK);
	GL_PageControls_TypeDef* DesignButton06= NewRectControl(6,210,100,NONE,ParametersRequireValueDosepH_DoseDay_pHScreen_Dose);
	Create_PageObj( &ParametersRequireValueDosepH_DoseDay_pHScreen ); 
	AddPageControlObj(250,240,DesignButton01,&ParametersRequireValueDosepH_DoseDay_pHScreen);
	AddPageControlObj(20,240,DesignButton02,&ParametersRequireValueDosepH_DoseDay_pHScreen);
	AddPageControlObj(20,170,DesignButton03,&ParametersRequireValueDosepH_DoseDay_pHScreen);
	AddPageControlObj(130,170,DesignButton04,&ParametersRequireValueDosepH_DoseDay_pHScreen);
	AddPageControlObj(250,170,DesignButton05,&ParametersRequireValueDosepH_DoseDay_pHScreen);
	AddPageControlObj(20,60,DesignButton06,&ParametersRequireValueDosepH_DoseDay_pHScreen);	
}
////////////////////////////////////////
void Show_ParametersRequireValueDosepH_DoseDay_pHScreen(void)
{
	UARTprintf("Show_ParametersRequireValueDosepH_DoseDay_pHScreen\r\n");
	Create_ParametersRequireValueDosepH_DoseDay_pHScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,290,(uint8_t *)"REQUIRED VALUES");
	LCD_DrawFullRect(20,60,210,100,VU_GRAY);
	LCD_DrawFullRect(250,60,210,100,VU_BLUE);
	LCD_SetBackColor(VU_GRAY);
	LCD_SetTextColor(BLACK);
	LCD_DisplayStringLine(70,30,(uint8_t *)"DOSE");
	LCD_DisplayStringLine(70,130,(uint8_t *)"ml/m3day");
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
	ParametersRequireValueDosepH_DoseDay_pHScreen.ShowPage(&ParametersRequireValueDosepH_DoseDay_pHScreen,GL_TRUE);
	Screen = ParametersRequireValueDosepH_DoseDay_pHScreen_df;
	CurrentScreen = &ParametersRequireValueDosepH_DoseDay_pHScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef CalibrationWaterScreen;
void Create_CalibrationWaterScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,CalibrationWaterScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,CalibrationWaterScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,GRAY_BLACK,CalibrationWaterScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,GRAY_BLACK,CalibrationWaterScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,GRAY_BLACK,CalibrationWaterScreen_OK);
	Create_PageObj( &CalibrationWaterScreen ); 
	AddPageControlObj(250,240,DesignButton01,&CalibrationWaterScreen);
	AddPageControlObj(20,240,DesignButton02,&CalibrationWaterScreen);
	AddPageControlObj(20,170,DesignButton03,&CalibrationWaterScreen);
	AddPageControlObj(130,170,DesignButton04,&CalibrationWaterScreen);
	AddPageControlObj(250,170,DesignButton05,&CalibrationWaterScreen);
}
////////////////////////////////////////
void Show_CalibrationWaterScreen(void)
{
	UARTprintf("Show_CalibrationWaterScreen\r\n");
	Create_CalibrationWaterScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,335,(uint8_t *)"CALIBRATION");
	LCD_DrawFullRect(250,60,210,100,VU_GRAY);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,30,(uint8_t *)"Thermometer calibration");
	LCD_DisplayStringLine(90,30,(uint8_t *)"range is 5 - 50 oC");
	LCD_SetBackColor(VU_GRAY);
	LCD_SetTextColor(WHITE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"TEMP.WATER");
	LCD_DrawFullRect(325,140,60,20,BLACK);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_GRAY);
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
	CalibrationWaterScreen.ShowPage(&CalibrationWaterScreen,GL_TRUE);
	Screen = CalibrationWaterScreen_df;
	CurrentScreen = &CalibrationWaterScreen;
}





/*Giao dien tu thiet ke*/
GL_Page_TypeDef CalibrationAirScreen;
void Create_CalibrationAirScreen(void)
{
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(1,210,30,WHITE,CalibrationAirScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(2,210,30,WHITE,CalibrationAirScreen_BackToStart);
	GL_PageControls_TypeDef* DesignButton03= NewRectControl(3,100,60,GRAY_BLACK,CalibrationAirScreen_inc);
	GL_PageControls_TypeDef* DesignButton04= NewRectControl(4,100,60,GRAY_BLACK,CalibrationAirScreen_dec);
	GL_PageControls_TypeDef* DesignButton05= NewRectControl(5,210,60,GRAY_BLACK,CalibrationAirScreen_OK);
	Create_PageObj( &CalibrationAirScreen ); 
	AddPageControlObj(250,240,DesignButton01,&CalibrationAirScreen);
	AddPageControlObj(20,240,DesignButton02,&CalibrationAirScreen);
	AddPageControlObj(20,170,DesignButton03,&CalibrationAirScreen);
	AddPageControlObj(130,170,DesignButton04,&CalibrationAirScreen);
	AddPageControlObj(250,170,DesignButton05,&CalibrationAirScreen);
}
////////////////////////////////////////
void Show_CalibrationAirScreen(void)
{
	UARTprintf("Show_CalibrationAirScreen\r\n");
	Create_CalibrationAirScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,335,(uint8_t *)"CALIBRATION");
	LCD_DrawFullRect(250,60,210,100,VU_GRAY);
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,30,(uint8_t *)"Thermometer calibration");
	LCD_DisplayStringLine(90,30,(uint8_t *)"range is 5 - 50 oC");
	LCD_SetBackColor(VU_GRAY);
	LCD_SetTextColor(WHITE);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(70,260,(uint8_t *)"TEMP.AIR");
	LCD_DrawFullRect(325,140,60,20,BLACK);
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetTextColor(VU_GRAY);
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
	CalibrationAirScreen.ShowPage(&CalibrationAirScreen,GL_TRUE);
	Screen = CalibrationAirScreen_df;
	CurrentScreen = &CalibrationAirScreen;
}






/*Giao dien tu thiet ke*/
GL_Page_TypeDef TypeOfProbeScreen;
void Create_TypeOfProbeScreen(void)
{
	GL_RadioButtonGrp_TypeDef* TypeOfProbe=NewRadioButtonGrp(1);
	GL_PageControls_TypeDef* DesignButton01= NewRectControl(4,210,30,WHITE,TypeOfProbeScreen_Back);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(5,210,30,WHITE,TypeOfProbeScreen_BackToStart);
	GL_PageControls_TypeDef* CheckBox1= RADIO_BUTTON_ADD(TypeOfProbe,(const uint8_t *)"",TypeOfProbeScreen_FreeChlorine);
	GL_PageControls_TypeDef* CheckBox2= RADIO_BUTTON_ADD(TypeOfProbe,(const uint8_t *)"",TypeOfProbeScreen_RedoxProbe);
	GL_PageControls_TypeDef* CheckBox3= RADIO_BUTTON_ADD(TypeOfProbe,(const uint8_t *)"",TypeOfProbeScreen_mlperhour);
	GL_PageControls_TypeDef* CheckBox4= RADIO_BUTTON_ADD(TypeOfProbe,(const uint8_t *)"",TypeOfProbeScreen_mlperday);
	Create_PageObj( &TypeOfProbeScreen ); 
	AddPageControlObj(250,240,DesignButton01,&TypeOfProbeScreen);
	AddPageControlObj(20,240,DesignButton02,&TypeOfProbeScreen);
	AddPageControlObj(20,65,CheckBox1,&TypeOfProbeScreen);
	AddPageControlObj(20,110,CheckBox2,&TypeOfProbeScreen);
	AddPageControlObj(20,155,CheckBox3,&TypeOfProbeScreen);
	AddPageControlObj(20,200,CheckBox4,&TypeOfProbeScreen);
	((GL_RadioOption_TypeDef*)(TypeOfProbe->RadioOptions[TypeofProbe]->objPTR))->IsChecked = GL_TRUE;
}
////////////////////////////////////////
void Show_TypeOfProbeScreen(void)
{
	UARTprintf("Create_TypeOfProbeScreen\r\n");
	Create_TypeOfProbeScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,185,(uint8_t *)"CHOOSE THE TYPE OF PROBE");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_DrawFullRect(250,240,210,30,WHITE);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(250,240,210,30,(uint8_t *)"BACK");
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,45,(uint8_t *)"free chlorine probe CLF");
	LCD_DisplayStringLine(115,45,(uint8_t *)"redox probe RX");
	LCD_DisplayStringLine(160,45,(uint8_t *)"time dosing ml/m3 per hour");
	LCD_DisplayStringLine(205,45,(uint8_t *)"time dosing ml/m3 per day");
	TypeOfProbeScreen.ShowPage(&TypeOfProbeScreen,GL_TRUE);
	Screen = TypeOfProbeScreen_df;
	CurrentScreen = &TypeOfProbeScreen;
}



/*Giao dien tu thiet ke*/
GL_Page_TypeDef LanguagesScreen;
void Create_LanguagesScreen(void)
{
	GL_RadioButtonGrp_TypeDef* Languages=NewRadioButtonGrp(1);
	GL_PageControls_TypeDef* DesignButton02= NewRectControl(5,210,30,WHITE,LanguagesScreen_BackToStart);
	GL_PageControls_TypeDef* CheckBox1= RADIO_BUTTON_ADD(Languages,(const uint8_t *)"",LanguagesScreen_Vietnamese);
	GL_PageControls_TypeDef* CheckBox2= RADIO_BUTTON_ADD(Languages,(const uint8_t *)"",LanguagesScreen_English);	
	Create_PageObj( &LanguagesScreen ); 
	AddPageControlObj(20,240,DesignButton02,&LanguagesScreen);
	AddPageControlObj(20,65,CheckBox1,&LanguagesScreen);
	AddPageControlObj(20,110,CheckBox2,&LanguagesScreen);
	((GL_RadioOption_TypeDef*)(Languages->RadioOptions[Languages_Choose]->objPTR))->IsChecked = GL_TRUE;
}
////////////////////////////////////////
void Show_LanguagesScreen(void)
{
	UARTprintf("Show_LanguagesScreen\r\n");
	Create_LanguagesScreen();
	LCD_Clear(BLACK);
	LCD_DrawFullRect(20,12,90,28,WHITE);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLine(14,20,(uint8_t *)"TITLE");
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font12x12);
	LCD_DisplayStringLine(20,280,(uint8_t *)"CHOOSE LANGUASES");
	LCD_DrawFullRect(20,240,210,30,WHITE);
	LCD_SetColors(BLACK,WHITE);
	LCD_DisplayStringLineInRect(20,240,210,30,(uint8_t *)"BACK TO START");	
	LCD_SetColors(WHITE,BLACK);
	LCD_SetFont(&Font8x12_bold);
	LCD_DisplayStringLine(70,45,(uint8_t *)"VietNamese");
	LCD_DisplayStringLine(115,45,(uint8_t *)"English");
	LanguagesScreen.ShowPage(&LanguagesScreen,GL_TRUE);
	Screen = LanguagesScreen_df;
	CurrentScreen = &LanguagesScreen;
}





/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 
