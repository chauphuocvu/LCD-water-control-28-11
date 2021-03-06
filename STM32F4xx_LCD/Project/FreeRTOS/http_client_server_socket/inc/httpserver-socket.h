/**
  ******************************************************************************
  * @file    httpserver-socket.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   header file for httpserver-socket.c
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HTTPSERVER_SOCKET_H__
#define __HTTPSERVER_SOCKET_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_uartstdio.h"
#include "debug.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#define SAFE	0
#define UNSAFE	1
void http_server_socket_init(void);
void DynWebPage(int conn);
void LoginPage(int conn);
void DynWebPageSettingByVu(int conn);
void DynWebPageByVu(int conn);
void GetTimePage(int conn);
/*chau phuoc vu 22/5/2019*/
extern char stringRedox[4];
extern char stringpH[4];
extern uint8_t time_out;
extern uint8_t security;
#endif /* __HTTPSERVER_SOCKET_H__ */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
