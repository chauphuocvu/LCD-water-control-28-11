/*******************************************************************************
* @file		: uiframework.h
* @author	: IMS Systems LAB & Technical Marketing
* @version	: V1.0.0
* @date		: 11-Apr-2017
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

extern GL_Page_TypeDef home;

/* Exported constants ----------------------------------------------------------*/

#define txt1Color 					17244
/* Exported macros -------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------*/
void Create_home(void);
void Show_home(void);
void Show_HomeScreen(void);




#ifdef __cplusplus
}
#endif

#endif /*__UIFRAMEWORK_H */ 

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/ 

