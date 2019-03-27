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
/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup User_Functions
  * @brief Contains event handlers for controls to execute the user code
  * @{
  */

/* External variables ----------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------*/
/* Private defines -------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------*/
/* Private functions -----------------------------------------------------------*/

/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option DesignOptionButton01
  * @param None
  * @retval None
  */
void screen_dos_button_Click()
{
	DestroyPage (&setting_screen);
	GL_Clear(BLACK);
	Create_dosingTest_screen();
	Show_dosingTest_screen();
}
/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option DesignOptionButton02
  * @param None
  * @retval None
  */
void screen1_DesignOptionButton02_Selected()
{
}
/**
  * @brief Option button selected event handler
  * @note This function gets called when user selects option DesignOptionButton03
  * @param None
  * @retval None
  */
void screen1_DesignOptionButton03_Selected()
{
}
/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  DesignButton01.
  * @param None
  * @retval None
  */
void screen1_DesignButton01_Click()
{
	DestroyPage (&home_screen);
	GL_Clear(BLACK);
	Create_setting_screen();
	Show_setting_screen();
	//LCD_DrawFullRect(20, 45, 210, 182, 32804);
	//LCD_DrawFullRect(250, 45, 210, 182, RGB565CONVERT(0, 4, 56));
}

void screen1_back_dos_button_Click(void)
{
	DestroyPage (&dosingTest_screen);
	GL_Clear(BLACK);
	Create_setting_screen();
	Show_setting_screen();
}

void screen1_back_param_button_Click (void) 
{
	DestroyPage (&param_screen);
	GL_Clear(BLACK);
	Create_setting_screen();
	Show_setting_screen();
}

void screen1_back_pool_button_Click(void)
{
	DestroyPage (&pool_param_screen);
	GL_Clear(BLACK);
	Create_param_screen();
	Show_param_screen();
}

void screen1_pro_button_Click(void)
{
	DestroyPage (&setting_screen);
	GL_Clear(BLACK);
	Create_probeType_screen();
	Show_probeType_screen();
}

void back_to_setting_back_dos_button_Click()
{
	DestroyPage (&dosingTest_screen);
	GL_Clear(BLACK);
	Create_setting_screen();
	Show_setting_screen();
}

/**
  * @brief Button click event handler
  * @note This function gets called when user clicks  DesignButton02.
  * @param None
  * @retval None
  */
void back_to_home_screen_back_button_Click()
{
	DestroyPage (&setting_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}

void screen1_back_ph_button_Click(void) 
{
	DestroyPage (&ph_param_screen);
	GL_Clear(BLACK);
	Create_param_screen();
	Show_param_screen();
}

void back_to_home_screen_ph_back_button_Click(void)
{
	DestroyPage (&ph_param_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}

void screen1_ph_button_Click(void)
{
	DestroyPage (&param_screen);
	GL_Clear(BLACK);
	Create_ph_param_screen();
	Show_ph_param_screen();
}

void back_to_home_screen_back_button_dos_Click()
{
	DestroyPage (&dosingTest_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}

void screen1_param_button_Click(void)
{
	DestroyPage (&setting_screen);
	GL_Clear(BLACK);
	Create_param_screen();
	Show_param_screen();
}

void back_to_home_screen_back_button_param_Click(void)
{
	DestroyPage (&param_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}

void screen1_pool_button_Click (void)
{
	DestroyPage (&param_screen);
	GL_Clear(BLACK);
	Create_pool_param_screen();
	Show_pool_param_screen();
}

void back_to_home_screen_pool_back_button_Click (void)
{
	DestroyPage (&pool_param_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}

void back_to_home_screen_water_back_button_Click (void)
{
	DestroyPage (&water_param_screen);
	GL_Clear(BLACK);
	Create_home_screen();
	Show_home_screen();
}
void screen1_back_water_button_Click(void)
{
	DestroyPage (&water_param_screen);
	GL_Clear(BLACK);
	Create_param_screen();
	Show_param_screen();
}
void screen1_water_button_Click (void)
{
	DestroyPage (&param_screen);
	GL_Clear(BLACK);
	Create_water_param_screen();
	Show_water_param_screen();
}
/**
  * @}
  */
/**
  * @brief Check box event handler
  * @note This function gets called when user clicks  CheckBox01.
  * @param None
  * @retval None
  */
void screen1_cb1_CheckChanged()
{
}
/**
  * @}
  */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

