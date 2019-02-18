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
#include <stdlib.h>
#include "uiframework.h"
#include "uiappuser.h"
#include "float.h"
#include "LcdHal.h"
#include "TscHal.h"
#include "pictures.h"
#include "fonts.h"
#include "images.h"


extern volatile uint16_t ADC_value;

GL_Page_TypeDef *CurrentScreen;

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
GL_Page_TypeDef home_screen;
GL_Page_TypeDef setting_screen;

GL_Page_TypeDef dosingTest_screen;
GL_Page_TypeDef param_screen;

GL_Page_TypeDef pool_param_screen;
GL_Page_TypeDef water_param_screen;
GL_Page_TypeDef ph_param_screen;
GL_Page_TypeDef probeType_screen;

/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/

/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_home_screen() 
{ 
	//GL_PageControls_TypeDef* DesignLabel01= NewLabel(1,"ASEKO",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	GL_PageControls_TypeDef* DesignLabel02= NewLabel(2,"ASI N Aqua",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* DesignLabel03= NewLabel(4,"Aseko Pool Technology",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	GL_PageControls_TypeDef* DesignLabel04= NewLabel(5,"CHLORI NE",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel03Color);
	GL_PageControls_TypeDef* DesignLabel05= NewLabel(6,"pH -",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel03Color);
	//GL_PageControls_TypeDef* DesignLabel06= NewLabel(7,"0,5",GL_HORIZONTAL,GL_FONT_BIG,DesignLabel03Color);
	
	GL_PageControls_TypeDef* DesignButton01= NewButton(3,"  SETTI NGS  ",screen1_DesignButton01_Click);
	Create_PageObj( &home_screen ); 
	//AddPageControlObj(10,10,DesignLabel01,&home_screen); 				//ASEKO
	AddPageControlObj(10, 235, DesignLabel02, &home_screen); 		// ASIN Aqua
	//AddPageControlObj(300, 10, DesignLabel03, &home_screen);		// Aseko Pool Technology
	AddPageControlObj(25, 50, DesignLabel04, &home_screen);			// CHLORINE
	//AddPageControlObj(95, 120, DesignLabel06, &home_screen);			// CHLORINE value
	AddPageControlObj(255, 50, DesignLabel05, &home_screen);		// pH -
	
	AddPageControlObj(350, 229, DesignButton01, &home_screen); // SETTINGS
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_home_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	GL_Clear(BLACK);
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	//GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// SETTING label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 230, "Aseko Pool Tech.", TRUE);

	GL_SetTextColor(65535);
	LCD_DrawFullRect(20, 45, 210, 172, 52804);
	LCD_DrawFullRect(250, 45, 210, 172, RGB565CONVERT(0, 159, 227));
	
	//GL_DisplayAdjStringLine(2, 2, "Le Nhat Thanh Print", TRUE); <-- this function worked
	home_screen.ShowPage(&home_screen, GL_TRUE);
	CurrentScreen=&home_screen; 
	
} 

/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_setting_screen() 
{ 
	GL_PageControls_TypeDef* param_button = NewButton(1,"TOUCH HERE",screen1_param_button_Click);
	GL_PageControls_TypeDef* cali_button = NewButton(2,"TOUCH HERE",screen1_DesignButton01_Click);
	GL_PageControls_TypeDef* dos_button = NewButton(3,"TOUCH HERE",screen_dos_button_Click);
	GL_PageControls_TypeDef* pro_button = NewButton(4,"TOUCH HERE",screen1_pro_button_Click);
	
	GL_PageControls_TypeDef* back_button = NewButton(5," BACH TO START ", back_to_home_screen_back_button_Click);
	GL_PageControls_TypeDef* lang_button = NewButton(6,"   LANGUAGE    ", screen1_DesignButton01_Click);
	
	Create_PageObj( &setting_screen ); 
	
	AddPageControlObj(90, 85, param_button, &setting_screen);
	AddPageControlObj(315, 85, cali_button, &setting_screen);
	AddPageControlObj(90, 185, dos_button, &setting_screen);
	AddPageControlObj(315, 185, pro_button, &setting_screen);
	
	AddPageControlObj(65, 229, back_button, &setting_screen);
	AddPageControlObj(290, 229, lang_button, &setting_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_setting_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// SETTING label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 350, "SETTINGS", TRUE);
	
	// 4 buttons of setting menu
	LCD_DrawRect(31, 46, 75, 195);
	LCD_DrawRect(256, 46, 75, 195);
	
	LCD_DrawRect(31, 146, 75, 195);
	LCD_DrawRect(256, 146, 75, 195);
	
	GL_DisplayAdjStringLine(51, 48, "PARAMETERS", TRUE);
	GL_DisplayAdjStringLine(51, 270, "CALIBRATION", TRUE);
	GL_DisplayAdjStringLine(151, 45, "DOSING TEST", TRUE);
	GL_DisplayAdjStringLine(151, 275, "PROBE TYPE", TRUE);
	
	
	LCD_DrawFullRect(31, 229, 195, 40, RGB565CONVERT(255, 255, 255));
	LCD_DrawFullRect(256, 229, 195, 40, RGB565CONVERT(255, 255, 255));
	// NOTE: Button event and icon will be created in Create_setting_screen() function
	
	/**** END Screen setting ****/
	
	setting_screen.ShowPage(&setting_screen, GL_TRUE);
	CurrentScreen=&setting_screen; 
	
} 

/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_dosingTest_screen() 
{
	GL_PageControls_TypeDef* back_button = NewButton(5," BACH TO START ", back_to_home_screen_back_button_dos_Click);
	GL_PageControls_TypeDef* back_dos_button = NewButton(6,"     BACK      ", screen1_back_dos_button_Click);
	
	Create_PageObj( &dosingTest_screen ); 
	
	AddPageControlObj(65, 229, back_button, &dosingTest_screen);
	AddPageControlObj(290, 229, back_dos_button, &dosingTest_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_dosingTest_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// DOSING TEST label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 300, "DOSING TEST", TRUE);
	
	// ---------------------
	LCD_DrawFullRect(20, 45, 210, 100, 52804);
	LCD_DrawFullRect(250, 45, 210, 100, RGB565CONVERT(0, 159, 227));
	
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(47, 22, "DISINF.", TRUE);
	GL_DisplayAdjStringLine(47, 252, "pH", TRUE);
	
	// Demo value
	GL_DisplayAdjStringLine(97, 72, "130 ml", TRUE);
	GL_DisplayAdjStringLine(97, 302, "125 ml", TRUE);
	
	GL_SetTextColor(RGB565CONVERT(255, 206, 68));
	LCD_DrawRect(31, 156, 55, 195);
	GL_SetTextColor(RGB565CONVERT(0, 159, 227));
	LCD_DrawRect(256, 156, 55, 195);
	
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(161, 85, "START", TRUE);
	GL_DisplayAdjStringLine(161, 315, "START", TRUE);
	
	// NOTE: Button event and icon will be created in Create_dosingTest_screen() function
	
	/**** END Screen setting ****/
	
	dosingTest_screen.ShowPage(&dosingTest_screen, GL_TRUE);
	CurrentScreen=&dosingTest_screen; 
	
} 


/**
  * @brief Create and configure screen object
  * @note This control creates the screen object and configures contained controls
  * @param None
  * @retval None
  */
void Create_param_screen() 
{ 
	GL_PageControls_TypeDef* pool_button = NewButton(1,"TOUCH HERE",screen1_pool_button_Click);
	GL_PageControls_TypeDef* water_button = NewButton(2,"TOUCH HERE",screen1_water_button_Click);
	
	GL_PageControls_TypeDef* ph_button = NewButton(3,"TOUCH HERE",screen1_ph_button_Click);
	GL_PageControls_TypeDef* disinfection_button = NewButton(4,"TOUCH HERE",screen1_water_button_Click);
	
	GL_PageControls_TypeDef* back_button = NewButton(5," BACH TO START ", back_to_home_screen_back_button_param_Click);
	GL_PageControls_TypeDef* back_param_button = NewButton(6,"     BACK      ", screen1_back_param_button_Click);
	
	Create_PageObj( &param_screen ); 
	
	AddPageControlObj(90, 85, pool_button, &param_screen);
	AddPageControlObj(315, 85, water_button, &param_screen);
	
	AddPageControlObj(65, 229, back_button, &param_screen);
	AddPageControlObj(290, 229, back_param_button, &param_screen);
	
	AddPageControlObj(90, 180, disinfection_button, &param_screen);
	AddPageControlObj(315, 180, ph_button, &param_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_param_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// DOSING TEST label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 300, "PARAMETERS", TRUE);
	
	// ---------------------
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	LCD_DrawRect(31, 46, 75, 195);
	LCD_DrawRect(256, 46, 75, 195);
	
	LCD_DrawFullRect(31, 146, 195, 75, 52804);
	LCD_DrawFullRect(256, 146, 195, 75, RGB565CONVERT(0, 159, 227));
	
	GL_DisplayAdjStringLine(51, 97, "POOL", TRUE);
	GL_DisplayAdjStringLine(51, 315, "WATER", TRUE);
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(151, 45, "DISINFECTION", TRUE);
	GL_DisplayAdjStringLine(151, 330, "pH", TRUE);
	
	// NOTE: Button event and icon will be created in Create_dosingTest_screen() function
	
	/**** END Screen setting ****/
	
	param_screen.ShowPage(&param_screen, GL_TRUE);
	CurrentScreen=&param_screen; 
	
} 


void Create_pool_param_screen() 
{ 
	//GL_PageControls_TypeDef* pool_button = NewButton(1,"TOUCH HERE",screen1_pool_button_Click);
	//GL_PageControls_TypeDef* water_button = NewButton(2,"TOUCH HERE",screen1_water_button_Click);
	//GL_PageControls_TypeDef* dos_button = NewButton(3,"TOUCH HERE",screen_dos_button_Click);
	//GL_PageControls_TypeDef* pro_button = NewButton(4,"TOUCH HERE",screen1_DesignButton01_Click);
	
	GL_PageControls_TypeDef* pool_back_button = NewButton(5," BACH TO START ", back_to_home_screen_pool_back_button_Click);
	GL_PageControls_TypeDef* back_pool_button = NewButton(6,"     BACK      ", screen1_back_pool_button_Click);
	
	Create_PageObj( &pool_param_screen ); 
	
	//AddPageControlObj(90, 85, pool_button, &param_screen);
	//AddPageControlObj(315, 85, water_button, &param_screen);
	//AddPageControlObj(90, 185, dos_button, &dosingTest_screen);
	//AddPageControlObj(315, 185, pro_button, &dosingTest_screen);
	
	AddPageControlObj(65, 229, pool_back_button, &pool_param_screen);
	AddPageControlObj(290, 229, back_pool_button, &pool_param_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_pool_param_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// DOSING TEST label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 250, "POOL PARAMETERS", TRUE);
	
	// ---------------------
	LCD_DrawFullRect(20, 45, 210, 100, RGB565CONVERT(87, 87, 86));
	LCD_DrawFullRect(250, 45, 210, 100, RGB565CONVERT(87, 87, 86));
	
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(47, 30, "POOL VOLUME", TRUE);
	GL_DisplayAdjStringLine(47, 305, "PERIOD", TRUE);
	
	// Demo value
	GL_DisplayAdjStringLine(97, 72, "30 m^2", TRUE);
	GL_DisplayAdjStringLine(97, 302, "06 h", TRUE);
	
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	LCD_DrawRect(31, 156, 55, 90);
	LCD_DrawRect(130, 156, 55, 90);
	LCD_DrawRect(256, 156, 55, 195);
	
	//GL_DisplayAdjStringLine(161, 85, "START", TRUE);
	//GL_DisplayAdjStringLine(161, 320, "OK", TRUE);
	
	// NOTE: Button event and icon will be created in Create_dosingTest_screen() function
	
	/**** END Screen setting ****/
	
	pool_param_screen.ShowPage(&pool_param_screen, GL_TRUE);
	CurrentScreen=&pool_param_screen; 
	
} 

void Create_water_param_screen() 
{ 
	GL_PageControls_TypeDef* water_back_button = NewButton(5," BACH TO START ", back_to_home_screen_water_back_button_Click);
	GL_PageControls_TypeDef* back_water_button = NewButton(6,"     BACK      ", screen1_back_water_button_Click);
	
	GL_RadioButtonGrp_TypeDef* Group01=NewRadioButtonGrp(1);
		GL_PageControls_TypeDef* DesignOptionButton01 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* DesignOptionButton02 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* DesignOptionButton03 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
	//GL_PageControls_TypeDef* Indoor = NewLabel(7,"Indoor",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Outdoor = NewLabel(8,"Outdoor",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Extreme = NewLabel(9,"Extreme",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	
	GL_RadioButtonGrp_TypeDef* Group02=NewRadioButtonGrp(2);
		GL_PageControls_TypeDef* Group02_01 = RADIO_BUTTON_ADD(Group02,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* Group02_02 = RADIO_BUTTON_ADD(Group02,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* Group02_03 = RADIO_BUTTON_ADD(Group02,"",screen1_back_water_button_Click);
	//GL_PageControls_TypeDef* Group02_01_label = NewLabel(10,"< 20 °C",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Group02_02_label = NewLabel(11,"20-30 °C",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Group02_03_label = NewLabel(12,"> 30 °C",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	
	GL_RadioButtonGrp_TypeDef* Group03=NewRadioButtonGrp(3);
		GL_PageControls_TypeDef* Group03_01 = RADIO_BUTTON_ADD(Group03,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* Group03_02 = RADIO_BUTTON_ADD(Group03,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* Group03_03 = RADIO_BUTTON_ADD(Group03,"",screen1_back_water_button_Click);
	//GL_PageControls_TypeDef* Group03_01_label = NewLabel(13,"Indoor",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Group03_02_label = NewLabel(14,"Outdoor",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	//GL_PageControls_TypeDef* Group03_03_label = NewLabel(15,"Extreme",GL_HORIZONTAL,GL_FONT_SMALL,DesignLabel01Color);
	
	Create_PageObj( &water_param_screen ); 
	
	AddPageControlObj(65, 229, water_back_button, &water_param_screen);
	AddPageControlObj(290, 229, back_water_button, &water_param_screen);
	
	AddPageControlObj(180,65,DesignOptionButton01,&water_param_screen);
	AddPageControlObj(280,65,DesignOptionButton02,&water_param_screen);
	AddPageControlObj(380,65,DesignOptionButton03,&water_param_screen);
	//AddPageControlObj(170,40,Indoor,&water_param_screen);
	//AddPageControlObj(270,40,Outdoor,&water_param_screen);
	//AddPageControlObj(370,40,Extreme,&water_param_screen);
	
	AddPageControlObj(180,129,Group02_01,&water_param_screen);
	AddPageControlObj(280,129,Group02_02,&water_param_screen);
	AddPageControlObj(380,129,Group02_03,&water_param_screen);
	//AddPageControlObj(170,110,Group02_01_label,&water_param_screen);
	//AddPageControlObj(270,110,Group02_02_label,&water_param_screen);
	//AddPageControlObj(370,110,Group02_03_label,&water_param_screen);
	
	AddPageControlObj(180,190,Group03_01,&water_param_screen);
	AddPageControlObj(280,190,Group03_02,&water_param_screen);
	AddPageControlObj(380,190,Group03_03,&water_param_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_water_param_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	LCD_DrawRect(133, 37, 53, 324);
	LCD_DrawRect(133, 100, 53, 324);
	LCD_DrawRect(133, 162, 53, 324);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// WATER PARAMETERS label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 245, "WATER PARAMETERS", TRUE);
	
	GL_DisplayAdjStringLine(50, 5, "POOL", TRUE);
	
	GL_DisplayAdjStringLine(105, 5, "AVERAGE", TRUE);
	GL_DisplayAdjStringLine(130, 5, "TEMP", TRUE);
	
	GL_DisplayAdjStringLine(170, 5, "WATER", TRUE);
	GL_DisplayAdjStringLine(190, 5, "HARDNESS", TRUE);
	
	GL_SetTextColor(RGB565CONVERT(255, 9, 9));
	GL_DisplayAdjStringLine(40, 135, "indoor", TRUE);
	GL_DisplayAdjStringLine(40, 235, "outdoor", TRUE);
	GL_DisplayAdjStringLine(40, 350, "extreme", TRUE);
	
	GL_DisplayAdjStringLine(106, 150, "<20C", TRUE);
	GL_DisplayAdjStringLine(106, 240, "20-30C", TRUE);
	GL_DisplayAdjStringLine(106, 353, ">30C", TRUE);
	
	GL_DisplayAdjStringLine(167, 157, "soft", TRUE);
	GL_DisplayAdjStringLine(167, 255, "hard", TRUE);
	GL_DisplayAdjStringLine(167, 347, "so hard", TRUE);
	
	water_param_screen.ShowPage(&water_param_screen, GL_TRUE);
	CurrentScreen=&water_param_screen; 
} 


void Create_ph_param_screen() 
{ 
	//GL_PageControls_TypeDef* pool_button = NewButton(1,"TOUCH HERE",screen1_pool_button_Click);
	//GL_PageControls_TypeDef* water_button = NewButton(2,"TOUCH HERE",screen1_water_button_Click);
	//GL_PageControls_TypeDef* dos_button = NewButton(3,"TOUCH HERE",screen_dos_button_Click);
	//GL_PageControls_TypeDef* pro_button = NewButton(4,"TOUCH HERE",screen1_DesignButton01_Click);
	
	GL_PageControls_TypeDef* pool_back_button = NewButton(5," BACH TO START ", back_to_home_screen_ph_back_button_Click);
	GL_PageControls_TypeDef* back_pool_button = NewButton(6,"     BACK      ", screen1_back_ph_button_Click);
	
	Create_PageObj( &ph_param_screen ); 
	
	//AddPageControlObj(90, 85, pool_button, &param_screen);
	//AddPageControlObj(315, 85, water_button, &param_screen);
	//AddPageControlObj(90, 185, dos_button, &dosingTest_screen);
	//AddPageControlObj(315, 185, pro_button, &dosingTest_screen);
	
	AddPageControlObj(65, 229, pool_back_button, &ph_param_screen);
	AddPageControlObj(290, 229, back_pool_button, &ph_param_screen);
}


/**
  * @brief Show screen object
  * @note This control displayed the specified screen object
  * @param None
  * @retval None
  */
void Show_ph_param_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// DOSING TEST label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 250, "REQUIRED VALUES", TRUE);
	
	// ---------------------
	LCD_DrawFullRect(20, 45, 210, 100, RGB565CONVERT(255, 206, 68));
	LCD_DrawFullRect(250, 45, 210, 100, RGB565CONVERT(0, 158, 226));
	
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(47, 30, "CLF", TRUE);
	GL_DisplayAdjStringLine(47, 257, "pH", TRUE);
	
	// Demo value
	GL_DisplayAdjStringLine(97, 72, "0,2 mg/l", TRUE);
	GL_DisplayAdjStringLine(97, 302, "7,0 pH", TRUE);
	
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	LCD_DrawRect(31, 156, 55, 90);
	LCD_DrawRect(130, 156, 55, 90);
	LCD_DrawRect(256, 156, 55, 195);
	
	//GL_DisplayAdjStringLine(161, 85, "START", TRUE);
	//GL_DisplayAdjStringLine(161, 320, "OK", TRUE);
	
	// NOTE: Button event and icon will be created in Create_dosingTest_screen() function
	
	/**** END Screen setting ****/
	
	ph_param_screen.ShowPage(&ph_param_screen, GL_TRUE);
	CurrentScreen=&ph_param_screen; 
	
} 

void Create_probeType_screen() 
{ 
	GL_PageControls_TypeDef* water_back_button = NewButton(5," BACH TO START ", back_to_home_screen_water_back_button_Click);
	GL_PageControls_TypeDef* back_water_button = NewButton(6,"     BACK      ", screen1_back_water_button_Click);
	
	GL_RadioButtonGrp_TypeDef* Group01=NewRadioButtonGrp(1);
		GL_PageControls_TypeDef* DesignOptionButton01 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* DesignOptionButton02 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
		GL_PageControls_TypeDef* DesignOptionButton03 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
		//GL_PageControls_TypeDef* DesignOptionButton04 = RADIO_BUTTON_ADD(Group01,"",screen1_back_water_button_Click);
	
	Create_PageObj( &probeType_screen ); 
	
	AddPageControlObj(65, 229, water_back_button, &probeType_screen);
	AddPageControlObj(290, 229, back_water_button, &probeType_screen);
	
	AddPageControlObj(30,50, DesignOptionButton01,&probeType_screen);
	AddPageControlObj(30,90, DesignOptionButton02,&probeType_screen);
	AddPageControlObj(30,130,DesignOptionButton03,&probeType_screen);
	//AddPageControlObj(30,170,DesignOptionButton04,&probeType_screen);
}

void Show_probeType_screen()
{ 
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	if(CurrentScreen!=GL_NULL)
	{
		CurrentScreen->ShowPage(CurrentScreen,GL_FALSE);
	}
	/**** Screen setting ****/
	GL_Clear(BLACK);
	
	// ASEKO logo
	LCD_SetFont(&Font8x12);
	LCD_DrawFullRect(3, 3, 82, 23, RGB565CONVERT(255, 255, 255));
	GL_SetTextColor(RGB565CONVERT(0, 0, 0));
	GL_DisplayAdjStringLine(5, 5, "ASEKO", TRUE);
	
	// WATER PARAMETERS label
	LCD_SetFont(&Font8x8);
	GL_SetTextColor(RGB565CONVERT(255, 255, 255));
	GL_DisplayAdjStringLine(5, 200, "CHOOSE PROBE TYPE", TRUE);
	
	probeType_screen.ShowPage(&probeType_screen, GL_TRUE);
	CurrentScreen=&probeType_screen; 
} 

/**
  * @brief Controls home screen
  * @param None
  * @retval None
  */
void Show_HomeScreen()
{
	Create_home_screen();
	Show_home_screen();
}

/**
  * @}
  */

/**
  * @}
  */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

