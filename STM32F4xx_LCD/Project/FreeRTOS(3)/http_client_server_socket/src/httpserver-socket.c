/**
  ******************************************************************************
  * @file    httpserver-socket.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011  
  * @brief   Basic http server implementation using LwIP socket API   
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
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"
#include "fs.h"
#include "fsdata.h"
#include "string.h"
#include "httpserver-socket.h"
// thanh included
#include "LcdHal.h"
#include "graphicObject.h"
#include "uiframework.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WEBSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 4 )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u32_t nPageHits = 0;
portCHAR PAGE_BODY2[3500];
portCHAR PAGE_BODY[1024];
extern volatile uint16_t ADC_value;
extern volatile uint16_t CL_ADC_value;

/* Private variables for pH and CL settings-----------------------------------*/
int ph_min = 6;   // default
int ph_max = 8;   // default
int cl_max = 6; // default x 10
int cl_min = 4; // default x 10

/* Format of dynamic web page: the page header */

static const unsigned char PAGE_START[] = {
0x3c,0x21,0x44,0x4f,0x43,0x54,0x59,0x50,0x45,0x20,0x68,0x74,0x6d,0x6c,0x20,0x50,
0x55,0x42,0x4c,0x49,0x43,0x20,0x22,0x2d,0x2f,0x2f,0x57,0x33,0x43,0x2f,0x2f,0x44,
0x54,0x44,0x20,0x48,0x54,0x4d,0x4c,0x20,0x34,0x2e,0x30,0x31,0x2f,0x2f,0x45,0x4e,
0x22,0x20,0x22,0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x77,0x77,0x77,0x2e,0x77,0x33,
0x2e,0x6f,0x72,0x67,0x2f,0x54,0x52,0x2f,0x68,0x74,0x6d,0x6c,0x34,0x2f,0x73,0x74,
0x72,0x69,0x63,0x74,0x2e,0x64,0x74,0x64,0x22,0x3e,0x0d,0x0a,0x3c,0x68,0x74,0x6d,
0x6c,0x3e,0x0d,0x0a,0x3c,0x68,0x65,0x61,0x64,0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x74,
0x69,0x74,0x6c,0x65,0x3e,0x53,0x54,0x4d,0x33,0x32,0x46,0x34,0x78,0x37,0x54,0x41,
0x53,0x4b,0x53,0x3c,0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,0x0d,0x0a,0x20,0x20,0x3c,
0x6d,0x65,0x74,0x61,0x20,0x68,0x74,0x74,0x70,0x2d,0x65,0x71,0x75,0x69,0x76,0x3d,
0x22,0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x54,0x79,0x70,0x65,0x22,0x0d,0x0a,
0x20,0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x3d,0x22,0x74,0x65,0x78,0x74,0x2f,0x68,
0x74,0x6d,0x6c,0x3b,0x20,0x63,0x68,0x61,0x72,0x73,0x65,0x74,0x3d,0x77,0x69,0x6e,
0x64,0x6f,0x77,0x73,0x2d,0x31,0x32,0x35,0x32,0x22,0x3e,0x0d,0x0a,0x20,0x20,0x3c,
0x6d,0x65,0x74,0x61,0x20,0x68,0x74,0x74,0x70,0x2d,0x65,0x71,0x75,0x69,0x76,0x3d,
0x22,0x72,0x65,0x66,0x72,0x65,0x73,0x68,0x22,0x20,0x63,0x6f,0x6e,0x74,0x65,0x6e,
0x74,0x3d,0x22,0x31,0x22,0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x6d,0x65,0x74,0x61,0x20,
0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x3d,0x22,0x4d,0x53,0x48,0x54,0x4d,0x4c,0x20,
0x36,0x2e,0x30,0x30,0x2e,0x32,0x38,0x30,0x30,0x2e,0x31,0x35,0x36,0x31,0x22,0x20,
0x6e,0x61,0x6d,0x65,0x3d,0x22,0x47,0x45,0x4e,0x45,0x52,0x41,0x54,0x4f,0x52,0x22,
0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x73,0x74,0x79,0x6c,0x65,0x20,0x3d,0x22,0x66,0x6f,
0x6e,0x74,0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x6e,0x6f,0x72,0x6d,0x61,
0x6c,0x3b,0x20,0x66,0x6f,0x6e,0x74,0x2d,0x66,0x61,0x6d,0x69,0x6c,0x79,0x3a,0x20,
0x56,0x65,0x72,0x64,0x61,0x6e,0x61,0x3b,0x22,0x3e,0x3c,0x2f,0x73,0x74,0x79,0x6c,
0x65,0x3e,0x0d,0x0a,0x3c,0x2f,0x68,0x65,0x61,0x64,0x3e,0x0d,0x0a,0x3c,0x62,0x6f,
0x64,0x79,0x3e,0x0d,0x0a,0x3c,0x68,0x34,0x3e,0x3c,0x73,0x6d,0x61,0x6c,0x6c,0x20,
0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x66,0x61,0x6d,0x69,
0x6c,0x79,0x3a,0x20,0x56,0x65,0x72,0x64,0x61,0x6e,0x61,0x3b,0x22,0x3e,0x3c,0x73,
0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x62,0x69,0x67,0x3e,0x3c,0x62,0x69,0x67,0x3e,0x3c,
0x62,0x69,0x67,0x0d,0x0a,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,
0x74,0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,0x64,0x3b,0x22,
0x3e,0x3c,0x62,0x69,0x67,0x3e,0x3c,0x73,0x74,0x72,0x6f,0x6e,0x67,0x3e,0x3c,0x65,
0x6d,0x3e,0x3c,0x73,0x70,0x61,0x6e,0x0d,0x0a,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,
0x22,0x66,0x6f,0x6e,0x74,0x2d,0x73,0x74,0x79,0x6c,0x65,0x3a,0x20,0x69,0x74,0x61,
0x6c,0x69,0x63,0x3b,0x22,0x3e,0x53,0x54,0x4d,0x33,0x32,0x46,0x34,0x78,0x37,0x20,
0x4c,0x69,0x73,0x74,0x20,0x6f,0x66,0x20,0x74,0x61,0x73,0x6b,0x73,0x20,0x61,0x6e,
0x64,0x0d,0x0a,0x74,0x68,0x65,0x69,0x72,0x20,0x73,0x74,0x61,0x74,0x75,0x73,0x3c,
0x2f,0x73,0x70,0x61,0x6e,0x3e,0x3c,0x2f,0x65,0x6d,0x3e,0x3c,0x2f,0x73,0x74,0x72,
0x6f,0x6e,0x67,0x3e,0x3c,0x2f,0x62,0x69,0x67,0x3e,0x3c,0x2f,0x62,0x69,0x67,0x3e,
0x3c,0x2f,0x62,0x69,0x67,0x3e,0x3c,0x2f,0x62,0x69,0x67,0x3e,0x3c,0x2f,0x73,0x6d,
0x61,0x6c,0x6c,0x3e,0x3c,0x2f,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x2f,0x68,0x34,
0x3e,0x0d,0x0a,0x3c,0x68,0x72,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x77,0x69,
0x64,0x74,0x68,0x3a,0x20,0x31,0x30,0x30,0x25,0x3b,0x20,0x68,0x65,0x69,0x67,0x68,
0x74,0x3a,0x20,0x32,0x70,0x78,0x3b,0x22,0x3e,0x3c,0x73,0x70,0x61,0x6e,0x0d,0x0a,
0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x77,0x65,0x69,
0x67,0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,0x64,0x3b,0x22,0x3e,0x0d,0x0a,0x3c,0x2f,
0x73,0x70,0x61,0x6e,0x3e,0x3c,0x73,0x70,0x61,0x6e,0x20,0x73,0x74,0x79,0x6c,0x65,
0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x62,
0x6f,0x6c,0x64,0x3b,0x22,0x3e,0x0d,0x0a,0x3c,0x74,0x61,0x62,0x6c,0x65,0x20,0x73,
0x74,0x79,0x6c,0x65,0x3d,0x22,0x77,0x69,0x64,0x74,0x68,0x3a,0x20,0x39,0x36,0x31,
0x70,0x78,0x3b,0x20,0x68,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x33,0x30,0x70,0x78,
0x3b,0x22,0x20,0x62,0x6f,0x72,0x64,0x65,0x72,0x3d,0x22,0x31,0x22,0x0d,0x0a,0x20,
0x63,0x65,0x6c,0x6c,0x70,0x61,0x64,0x64,0x69,0x6e,0x67,0x3d,0x22,0x32,0x22,0x20,
0x63,0x65,0x6c,0x6c,0x73,0x70,0x61,0x63,0x69,0x6e,0x67,0x3d,0x22,0x32,0x22,0x3e,
0x0d,0x0a,0x20,0x20,0x3c,0x74,0x62,0x6f,0x64,0x79,0x3e,0x0d,0x0a,0x20,0x20,0x20,
0x20,0x3c,0x74,0x72,0x3e,0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x3c,0x74,0x64,
0x0d,0x0a,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x66,
0x61,0x6d,0x69,0x6c,0x79,0x3a,0x20,0x56,0x65,0x72,0x64,0x61,0x6e,0x61,0x3b,0x20,
0x66,0x6f,0x6e,0x74,0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,
0x64,0x3b,0x20,0x66,0x6f,0x6e,0x74,0x2d,0x73,0x74,0x79,0x6c,0x65,0x3a,0x20,0x69,
0x74,0x61,0x6c,0x69,0x63,0x3b,0x20,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,
0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x20,0x72,0x67,0x62,0x28,0x35,0x31,0x2c,
0x20,0x35,0x31,0x2c,0x20,0x32,0x35,0x35,0x29,0x3b,0x20,0x74,0x65,0x78,0x74,0x2d,
0x61,0x6c,0x69,0x67,0x6e,0x3a,0x20,0x63,0x65,0x6e,0x74,0x65,0x72,0x3b,0x22,0x3e,
0x3c,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x61,0x0d,0x0a,0x20,0x68,0x72,0x65,0x66,
0x3d,0x22,0x2f,0x53,0x54,0x4d,0x33,0x32,0x46,0x34,0x78,0x37,0x2e,0x68,0x74,0x6d,
0x6c,0x22,0x3e,0x3c,0x73,0x70,0x61,0x6e,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,
0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x20,0x77,0x68,0x69,0x74,0x65,0x3b,0x22,0x3e,0x48,
0x6f,0x6d,0x65,0x0d,0x0a,0x70,0x61,0x67,0x65,0x3c,0x2f,0x73,0x70,0x61,0x6e,0x3e,
0x3c,0x2f,0x61,0x3e,0x3c,0x2f,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x2f,0x74,0x64,
0x3e,0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x3c,0x74,0x64,0x0d,0x0a,0x20,0x73,
0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x66,0x61,0x6d,0x69,0x6c,
0x79,0x3a,0x20,0x56,0x65,0x72,0x64,0x61,0x6e,0x61,0x3b,0x20,0x66,0x6f,0x6e,0x74,
0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,0x64,0x3b,0x20,0x66,
0x6f,0x6e,0x74,0x2d,0x73,0x74,0x79,0x6c,0x65,0x3a,0x20,0x69,0x74,0x61,0x6c,0x69,
0x63,0x3b,0x20,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,
0x6c,0x6f,0x72,0x3a,0x20,0x72,0x67,0x62,0x28,0x35,0x31,0x2c,0x20,0x35,0x31,0x2c,
0x20,0x32,0x35,0x35,0x29,0x3b,0x20,0x74,0x65,0x78,0x74,0x2d,0x61,0x6c,0x69,0x67,
0x6e,0x3a,0x20,0x63,0x65,0x6e,0x74,0x65,0x72,0x3b,0x22,0x3e,0x3c,0x61,0x0d,0x0a,
0x20,0x68,0x72,0x65,0x66,0x3d,0x22,0x53,0x54,0x4d,0x33,0x32,0x46,0x34,0x78,0x37,
0x41,0x44,0x43,0x2e,0x68,0x74,0x6d,0x6c,0x22,0x3e,0x3c,0x73,0x70,0x61,0x6e,0x20,
0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,0x74,0x2d,0x77,0x65,0x69,0x67,
0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,0x64,0x3b,0x22,0x3e,0x3c,0x2f,0x73,0x70,0x61,
0x6e,0x3e,0x3c,0x2f,0x61,0x3e,0x3c,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x61,0x0d,
0x0a,0x20,0x68,0x72,0x65,0x66,0x3d,0x22,0x2f,0x53,0x54,0x4d,0x33,0x32,0x46,0x34,
0x78,0x37,0x54,0x41,0x53,0x4b,0x53,0x2e,0x68,0x74,0x6d,0x6c,0x22,0x3e,0x3c,0x73,
0x70,0x61,0x6e,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x63,0x6f,0x6c,0x6f,0x72,
0x3a,0x20,0x77,0x68,0x69,0x74,0x65,0x3b,0x22,0x3e,0x4c,0x69,0x73,0x74,0x0d,0x0a,
0x6f,0x66,0x20,0x74,0x61,0x73,0x6b,0x73,0x3c,0x2f,0x73,0x70,0x61,0x6e,0x3e,0x3c,
0x2f,0x61,0x3e,0x3c,0x2f,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,0x2f,0x74,0x64,0x3e,
0x0d,0x0a,0x20,0x20,0x20,0x20,0x3c,0x2f,0x74,0x72,0x3e,0x0d,0x0a,0x20,0x20,0x3c,
0x2f,0x74,0x62,0x6f,0x64,0x79,0x3e,0x0d,0x0a,0x3c,0x2f,0x74,0x61,0x62,0x6c,0x65,
0x3e,0x0d,0x0a,0x3c,0x62,0x72,0x3e,0x0d,0x0a,0x3c,0x2f,0x73,0x70,0x61,0x6e,0x3e,
0x3c,0x73,0x70,0x61,0x6e,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,0x6e,
0x74,0x2d,0x77,0x65,0x69,0x67,0x68,0x74,0x3a,0x20,0x62,0x6f,0x6c,0x64,0x3b,0x22,
0x3e,0x3c,0x2f,0x73,0x70,0x61,0x6e,0x3e,0x3c,0x73,0x6d,0x61,0x6c,0x6c,0x3e,0x3c,
0x73,0x70,0x61,0x6e,0x0d,0x0a,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x66,0x6f,
0x6e,0x74,0x2d,0x66,0x61,0x6d,0x69,0x6c,0x79,0x3a,0x20,0x56,0x65,0x72,0x64,0x61,
0x6e,0x61,0x3b,0x22,0x3e,0x4e,0x75,0x6d,0x62,0x65,0x72,0x20,0x6f,0x66,0x20,0x70,
0x61,0x67,0x65,0x20,0x68,0x69,0x74,0x73,0x3a,0x0d,0x0a,0x00};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief serve tcp connection  
  * @param conn: connection socket 
  * @retval None
  */
void http_server_serve(int conn) 
{
  int buflen = 1900;
  int ret;
  struct fs_file * file;
  unsigned char recv_buffer[1900];
				
  /* Read in the request */
  ret = read(conn, recv_buffer, buflen); 
  if(ret < 0) return;

  /* Check if request to get ST.gif */
  if (strncmp((char *)recv_buffer,"GET /STM32F4x7_files/ST.gif",27)==0)
  {
    file = fs_open("/STM32F4x7_files/ST.gif"); 
    write(conn, (const unsigned char*)(file->data), (size_t)file->len);
    if(file) fs_close(file);
  }
  /* Check if request to get stm32.jpeg */
  else if (strncmp((char *)recv_buffer,"GET /STM32F4x7_files/stm32.jpg",30)==0)
  {
    file = fs_open("/STM32F4x7_files/stm32.jpg"); 
    write(conn, (const unsigned char*)(file->data), (size_t)file->len);
    if(file) fs_close(file);
  }
  /* Check if request to get ST logo.jpeg */
  else if (strncmp((char *)recv_buffer,"GET /STM32F4x7_files/logo.jpg", 29) == 0)
  {
    file = fs_open("/STM32F4x7_files/logo.png"); 
    write(conn, (const unsigned char*)(file->data), (size_t)file->len);
    if(file) fs_close(file);
  }
  else if(strncmp((char *)recv_buffer, "GET /STM32F4x7TASKS.html", 24) == 0)
  {
    /* Load dynamic page */
    DynWebPage(conn);
  }
  else if((strncmp((char *)recv_buffer, "GET /STM32F4x7.html", 19) == 0)||(strncmp((char *)recv_buffer, "GET / ", 6) == 0))
  {
    /* Load STM32F4x7 page */
    file = fs_open("/STM32F4x7.html"); 
    write(conn, (const unsigned char*)(file->data), (size_t)file->len);
    if(file) fs_close(file);
  }
	//------------------------------------ GET /phvalue?ph_min=6&ph_max=8
	//------------------------------------ GET /phvalue?ph_min=6&ph_max=12
	else if (strncmp((char *)recv_buffer, "GET /phvalue", 12) == 0)
	{
		ph_min = recv_buffer[20] - 48;
		ph_max = recv_buffer[29] - 48;
		
		DynWebPageSettingByThanh(conn);
		
	}
	//------------------------------------ GET /clvalue?ph_min=0.4&ph_max=0.6
	//------------------------------------ GET /clvalue?ph_min=6&ph_max=12
	else if (strncmp((char *)recv_buffer, "GET /clvalue", 12) == 0)
	{
		cl_min = recv_buffer[22] - 48;
		cl_max = recv_buffer[33] - 48;

		DynWebPageSettingByThanh(conn);
	}
	else if (strncmp((char *)recv_buffer, "GET /control", 12) == 0)
	{
		DynWebPageByThanh(conn);
	}
	else if (strncmp((char *)recv_buffer, "GET /setting", 12) == 0)
	{
		DynWebPageSettingByThanh(conn);
	}
  else
  {
    /* Load 404 page */
    file = fs_open("/404.html"); 
    write(conn, (const unsigned char*)(file->data), (size_t)file->len);
    if(file) fs_close(file);
  }
  /* Close connection socket */
  close(conn);
}

/**
  * @brief  http server thread 
  * @param arg: pointer on argument(not used here) 
  * @retval None
  */
static void http_server_socket_thread(void *arg)
{
  int sock, newconn, size;
  struct sockaddr_in address, remotehost;

 /* create a TCP socket */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
  {
    DBG("can not create socket");
    return;
  }
  
  /* bind to port 80 at any interface */
  address.sin_family = AF_INET;
  address.sin_port = htons(80);
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr *)&address, sizeof (address)) < 0)
  {
    DBG("can not bind socket");
    return;
  }
  
  /* listen for incoming connections (TCP listen backlog = 5) */
  listen(sock, 5);
  
  size = sizeof(remotehost);
  
  while (1) 
  {
    newconn = accept(sock, (struct sockaddr *)&remotehost, (socklen_t *)&size);
    http_server_serve(newconn);
		//DBG("NEWCONN: %d\n",newconn);
		vTaskDelay(10);
  }
}

/**
  * @brief  Initialize the HTTP server (start its thread) 
  * @param  none
  * @retval None
  */
void http_server_socket_init()
{
  sys_thread_new("HTTPSERVER", http_server_socket_thread, NULL, DEFAULT_THREAD_STACKSIZE * 2, WEBSERVER_THREAD_PRIO);
}

/**
  * @brief  Create and send a dynamic Web Page. This page contains the list of 
  *         running tasks and the number of page hits. 
  * @param  conn connection socket
  * @retval None
  */

void DynWebPage(int conn)
{
  portCHAR pagehits[10];

  memset(PAGE_BODY, 0,1024);

  /* Update the hit count */
  nPageHits++;
  sprintf( pagehits, "%d", nPageHits );
  strcat(PAGE_BODY, pagehits);
  strcat((char *) PAGE_BODY, "<pre><br>Name          State  Priority  Stack   Num" );
  strcat((char *) PAGE_BODY, "<br>---------------------------------------------<br>"); 
    
  /* The list of tasks and their status */
  vTaskList((signed char *)(PAGE_BODY + strlen(PAGE_BODY)));
  strcat((char *) PAGE_BODY, "<br><br>---------------------------------------------"); 
  strcat((char *) PAGE_BODY, "<br>B : Blocked, R : Ready, D : Deleted, S : Suspended<br>");
	
	strcat((char *) PAGE_BODY, "<br><br>");

		
	// Convert ADC value to PH value with: PH_value = 14 * ADC_value / 4096
			int PH_value = 14 * ADC_value / 4096;
			
			int PH_value_r = (14 * ADC_value) % 4096;
			float PH_value_r_float = (float)PH_value_r / (float)4096;
			PH_value_r = (int)(PH_value_r_float * 10);
			char array[6] = {(PH_value / 10) + 48, (PH_value % 10) + 48, ',', PH_value_r + 48, 'p', 'H'};
			char * string = array;
	// --------------------------------------------------------------------
	strcat((char *) PAGE_BODY, "<h1>pH value: ");		
	strcat((char *) PAGE_BODY, string) ;
	strcat((char *) PAGE_BODY, "</h1>");
			
	/* LCD draw via web server demo */
			strcat((char *) PAGE_BODY, "<form action=\"/drawlcd\" method=\"GET\">");
			strcat((char *) PAGE_BODY, "  <input type=\"submit\" value=\"Show Setting Screen\">");
			
			strcat((char *) PAGE_BODY, "  <br>Test value:<br>");
			strcat((char *) PAGE_BODY, "  <input type=\"text\" name=\"testValue\" placeholder=\"Type the value here\">");
			strcat((char *) PAGE_BODY, "</form>");
	/* LCD draw via web server demo */
			
  /* Send the dynamically generated page */
  write(conn, PAGE_START, strlen((char*)PAGE_START));
  write(conn, PAGE_BODY, strlen(PAGE_BODY));
}

/**
  * @brief  Create and send a dynamic Web Page. This page contains the list of 
  *         running tasks and the number of page hits. 
  * @param  conn connection socket
  * @retval None
  */
void DynWebPageByThanh(int conn)
{
	
	memset(PAGE_BODY2, 0,3500);
	strcat((char *) PAGE_BODY2, "<html>" );
	strcat((char *) PAGE_BODY2, " <head>" );
	strcat((char *) PAGE_BODY2, " <title>Web server</title>" );
	strcat((char *) PAGE_BODY2, " <meta name=\"description\" content=\"Webserver\"/>" );
	strcat((char *) PAGE_BODY2, " <meta name=\"keyword\" content=\"ubuntu\"/>" );
	strcat((char *) PAGE_BODY2, " <meta charset=\"utf-8\"/>" );
	strcat((char *) PAGE_BODY2, " <meta http-equiv=\"refresh\" content=\"1\">" ); // auto refresh in 1s
	strcat((char *) PAGE_BODY2, " <style>" );
	strcat((char *) PAGE_BODY2, "* {" );
	strcat((char *) PAGE_BODY2, "box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "-moz-box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "-webkit-box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "body {" );
	strcat((char *) PAGE_BODY2, "font-family: \"Helvetiaca Neue\", Helvetiaca, Arial, sans-serif;" );
	strcat((char *) PAGE_BODY2, "font-weight: 300px;" );
	strcat((char *) PAGE_BODY2, "color: #333;" );
	strcat((char *) PAGE_BODY2, "line-height: 1.254;" );
	strcat((char *) PAGE_BODY2, "margin: 0;" );
	strcat((char *) PAGE_BODY2, "padding: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "a {" );
	strcat((char *) PAGE_BODY2, "text-decoration: none;" );
	strcat((char *) PAGE_BODY2, "color: #3b8bba;" );
	strcat((char *) PAGE_BODY2, "transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "-moz-transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "-webkit-transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "a:hover, a:visited {" );
	strcat((char *) PAGE_BODY2, "color: #265778;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#container {" );
	strcat((char *) PAGE_BODY2, "padding-left: 150px;" );
	strcat((char *) PAGE_BODY2, "position: relative;" );
	strcat((char *) PAGE_BODY2, "left: 0;" );
	strcat((char *) PAGE_BODY2, "width: 100%;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu {" );
	strcat((char *) PAGE_BODY2, "position: fixed;" );
	strcat((char *) PAGE_BODY2, "height: 100%;" );
	strcat((char *) PAGE_BODY2, "background-color: #191818;" );
	strcat((char *) PAGE_BODY2, "width: 150px;" );
	strcat((char *) PAGE_BODY2, "left: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu {}" );
	strcat((char *) PAGE_BODY2, "#menu ul{" );
	strcat((char *) PAGE_BODY2, "list-style-type: none;" );
	strcat((char *) PAGE_BODY2, "padding: 0;" );
	strcat((char *) PAGE_BODY2, "margin: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li {" );
	strcat((char *) PAGE_BODY2, "line-height: 2.9em;" );
	strcat((char *) PAGE_BODY2, "height: 2.9em; " );
	strcat((char *) PAGE_BODY2, "transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "-moz-transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "-webkit-transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "position: relative;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li a {" );
	strcat((char *) PAGE_BODY2, "display: block;" );
	strcat((char *) PAGE_BODY2, "color: #fff;" );
	strcat((char *) PAGE_BODY2, "padding: 0 1em;" );
	strcat((char *) PAGE_BODY2, "border-bottom: 1px solid #333;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li:hover {" );
	strcat((char *) PAGE_BODY2, "background-color: #454545;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu .sub-menu {" );
	strcat((char *) PAGE_BODY2, "display: none;" );
	strcat((char *) PAGE_BODY2, "position: absolute;" );
	strcat((char *) PAGE_BODY2, "top: 0;" );
	strcat((char *) PAGE_BODY2, "left: 150px;" );
	strcat((char *) PAGE_BODY2, "background-color: #191818;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li:hover .sub-menu{" );
	strcat((char *) PAGE_BODY2, "display: block;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#content {" );
	strcat((char *) PAGE_BODY2, "padding: 1em 8em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#header, .call-to-action {" );
	strcat((char *) PAGE_BODY2, "text-align:  center;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#header {}" );
	strcat((char *) PAGE_BODY2, "#header #logo {font-size:40px;}" );
	strcat((char *) PAGE_BODY2, "#header #slogan {" );
	strcat((char *) PAGE_BODY2, "color: 8997a0;" );
	strcat((char *) PAGE_BODY2, "font-size: 0.8em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".call-to-action {" );
	strcat((char *) PAGE_BODY2, "padding: 1.5em 20%;" );
	strcat((char *) PAGE_BODY2, "background-color: #f0ffff;" );
	strcat((char *) PAGE_BODY2, "border: 1px solid #e8e8e8;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row {" );
	strcat((char *) PAGE_BODY2, "overflow: hidden;" );
	strcat((char *) PAGE_BODY2, "margin: 1.5em auto;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col {" );
	strcat((char *) PAGE_BODY2, "float: left;" );
	strcat((char *) PAGE_BODY2, "width: 40%;" );
	strcat((char *) PAGE_BODY2, "margin: 2em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col:last-child {" );
	strcat((char *) PAGE_BODY2, "float: right;" );
	strcat((char *) PAGE_BODY2, "margin-right: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col img {" );
	strcat((char *) PAGE_BODY2, "float: left;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#footer {" );
	strcat((char *) PAGE_BODY2, "font-size: 85%;" );
	strcat((char *) PAGE_BODY2, "border-top: 1px solid #e6e6e6;" );
	strcat((char *) PAGE_BODY2, "color: #838383;" );
	strcat((char *) PAGE_BODY2, "padding: 1em 3em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#pH { padding:20px; border: 3px solid #ccc; border-radius:16px;text-align: center; }" );
	strcat((char *) PAGE_BODY2, "#warningPH, #warningCL {width: 100%;padding: 20px 0;text-align: center;background-color: #EFCD16;margin-top: 20px;font-size: 18px;border-radius: 5px;display:none;}" );

	strcat((char *) PAGE_BODY2, "</style>" );
	strcat((char *) PAGE_BODY2, " </head>" );
	strcat((char *) PAGE_BODY2, " <body>" );
	strcat((char *) PAGE_BODY2, " <div id=\"container\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"menu\">" );
	strcat((char *) PAGE_BODY2, " <ul>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"/control\">Homepage</a></li>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"/setting\">Settings</a></li>" );
	//strcat((char *) PAGE_BODY2, " <li><a href=\"#\">LED</a></li>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"#\">About</a></li>" );
	strcat((char *) PAGE_BODY2, " </ul>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " <div id=\"content\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"header\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"logo\">WebServer for LCD water control</div>" );
	strcat((char *) PAGE_BODY2, " <div id=\"slogan\">" );
	strcat((char *) PAGE_BODY2, " <p>Web control demo for STM32F4xx</p>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div><!header>" );
	strcat((char *) PAGE_BODY2, " <div class=\"call-to-action\">" );
	strcat((char *) PAGE_BODY2, " <h3>LCD water control via website</h3>" );
	strcat((char *) PAGE_BODY2, " <p>pH and CHL control</p>" );
	strcat((char *) PAGE_BODY2, " </div><!call-to-action>" );
	strcat((char *) PAGE_BODY2, " <div class=\"row\" id=\"intro\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"box1\" class=\"col\">" );
	
	strcat((char *) PAGE_BODY2, "<div style=\"margin-bottom:80px;border:2px solid;background: azure;border-radius: 5px;\">");
	strcat((char *) PAGE_BODY2, "<h3 style=\"text-align:center;\">pH settings</h3>");
	strcat((char *) PAGE_BODY2, "<p style=\"float:left;font-weight: bold;\">Minimum value: ");
	
	char ph_min_st[1] = { ph_min + 48 };
	strcat((char *) PAGE_BODY2, ph_min_st);
	
	strcat((char *) PAGE_BODY2, "</p>");
	strcat((char *) PAGE_BODY2, "<p style=\"float:right;font-weight: bold;\">Maximum value: ");
	
	char ph_max_st[1] = { ph_max + 48 };
	strcat((char *) PAGE_BODY2, ph_max_st);
	
	strcat((char *) PAGE_BODY2, "</p>");
	strcat((char *) PAGE_BODY2, "</div>");
	
/* Region for ADC reading */
			// Convert ADC value to PH value with: PH_value = 14 * ADC_value / 4096
			int PH_value = 14 * ADC_value / 4096;
			
			int PH_value_r = (14 * ADC_value) % 4096;
			float PH_value_r_float = (float)PH_value_r / (float)4096;
			PH_value_r = (int)(PH_value_r_float * 10);
			char array[6] = {(PH_value / 10) + 48, (PH_value % 10) + 48, ',', PH_value_r + 48, 'p', 'H'};
			char * string = array;
			
			
			int CL_value = 1 * CL_ADC_value / 4096;
			
			float CL_value_r_float = (float)CL_ADC_value / (float)4096;
			int CL_value_r = (int)(CL_value_r_float * 10);
			int CL_value_r_100 = (int)(CL_value_r_float * 100) - CL_value_r * 10;
			char array2[5] = {'0', ',', CL_value_r + 48, CL_value_r_100 + 48, '\0'};
			char* string2 = array2;		
			
			// --------------------------------------------------------------------
			strcat((char *) PAGE_BODY2, "<h1 id=\"pH\">pH value: <span style=\"color:#009EE2\">");		
	strcat((char *) PAGE_BODY2, string) ;
	strcat((char *) PAGE_BODY2, "</span></h1>");
			
	// if pH >= 8.0. Show a warning.
	strcat((char *) PAGE_BODY2, "<div id=\"warningPH\"><span style=\"color: red; font-weight: bold;\">Warning</span>: pH value is not allow!</div>");
	
			// js for warning
	strcat((char *) PAGE_BODY2, "<script>window.onload = function(){var x = document.getElementById(\"warningPH\"); var y = document.getElementById(\"warningCL\");");
	if( (PH_value >= ph_max  && PH_value_r > 0)|| PH_value < ph_min)
	{
		strcat((char *) PAGE_BODY2, "x.style.display = \"block\";");
	}
	else 
	{
		strcat((char *) PAGE_BODY2, "x.style.display = \"none\";");
	}
	
	if((CL_value_r >= cl_max && CL_value_r_100 > 0) || CL_value_r < cl_min )
	{
		strcat((char *) PAGE_BODY2, "y.style.display = \"block\";");
	}
	else 
	{
		strcat((char *) PAGE_BODY2, "y.style.display = \"none\";");
	}
	
	strcat((char *) PAGE_BODY2, "};</script>");
/* Region for ADC reading */
			
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " <div id=\"box2\" class=\"col\">" );
			
	strcat((char *) PAGE_BODY2, "<div style=\"margin-bottom:80px;border:2px solid;background: azure;border-radius: 5px;\">");
	strcat((char *) PAGE_BODY2, "<h3 style=\"text-align:center;\">CL settings</h3>");
	
	
	strcat((char *) PAGE_BODY2, "<p style=\"float:left;font-weight: bold;\">Minimum value: ");
	
	char cl_min_st[3] = { '0', '.', cl_min + 48 };
	strcat((char *) PAGE_BODY2, cl_min_st);
	
	strcat((char *) PAGE_BODY2, "</p>");
	strcat((char *) PAGE_BODY2, "<p style=\"float:right;font-weight: bold;\">Maximum value: ");
	
	char cl_max_st[3] = { '0', '.', cl_max + 48 };
	strcat((char *) PAGE_BODY2, cl_max_st);
	
	strcat((char *) PAGE_BODY2, "</p>");
	
	strcat((char *) PAGE_BODY2, "</div>");
	
/* Region for ADC reading */

	strcat((char *) PAGE_BODY2, "<h1 id=\"pH\">CHLORINE: <span style=\"color:#009EE2\">");		
	strcat((char *) PAGE_BODY2, string2) ;
	strcat((char *) PAGE_BODY2, "</span></h1>");

	// if CL >= 0.6. Show a warning.
	strcat((char *) PAGE_BODY2, "<div id=\"warningCL\"><span style=\"color: red; font-weight: bold;\">Warning</span>: CL value is not allow!</div>");
/* Region for ADC reading */
			
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div><!row>" );
	strcat((char *) PAGE_BODY2, " <div id=\"footer\">" );
	strcat((char *) PAGE_BODY2, " <p>Copyright &copy; Le Nhat Thanh</p>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </body>" );
	strcat((char *) PAGE_BODY2, " </html>" );

  write(conn, PAGE_BODY2, strlen(PAGE_BODY2));
}

/**
  * @brief  Create and send a dynamic Web Page. This page contains the list of 
  *         running tasks and the number of page hits. 
  * @param  conn connection socket
  * @retval None
  */
void DynWebPageSettingByThanh(int conn)
{
	
	memset(PAGE_BODY2, 0,3500);
	strcat((char *) PAGE_BODY2, "<html>" );
	strcat((char *) PAGE_BODY2, " <head>" );
	strcat((char *) PAGE_BODY2, " <title>Web server</title>" );
	strcat((char *) PAGE_BODY2, " <meta name=\"description\" content=\"Webserver\"/>" );
	strcat((char *) PAGE_BODY2, " <meta name=\"keyword\" content=\"ubuntu\"/>" );
	strcat((char *) PAGE_BODY2, " <meta charset=\"utf-8\"/>" );
	//strcat((char *) PAGE_BODY2, " <meta http-equiv=\"refresh\" content=\"1\">" ); // auto refresh in 1s
	strcat((char *) PAGE_BODY2, " <style>" );
	strcat((char *) PAGE_BODY2, "* {" );
	strcat((char *) PAGE_BODY2, "box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "-moz-box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "-webkit-box-sizing: border-box;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "body {" );
	strcat((char *) PAGE_BODY2, "font-family: \"Helvetiaca Neue\", Helvetiaca, Arial, sans-serif;" );
	strcat((char *) PAGE_BODY2, "font-weight: 300px;" );
	strcat((char *) PAGE_BODY2, "color: #333;" );
	strcat((char *) PAGE_BODY2, "line-height: 1.254;" );
	strcat((char *) PAGE_BODY2, "margin: 0;" );
	strcat((char *) PAGE_BODY2, "padding: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "a {" );
	strcat((char *) PAGE_BODY2, "text-decoration: none;" );
	strcat((char *) PAGE_BODY2, "color: #3b8bba;" );
	strcat((char *) PAGE_BODY2, "transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "-moz-transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "-webkit-transform: all 0.5s;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "a:hover, a:visited {" );
	strcat((char *) PAGE_BODY2, "color: #265778;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#container {" );
	strcat((char *) PAGE_BODY2, "padding-left: 150px;" );
	strcat((char *) PAGE_BODY2, "position: relative;" );
	strcat((char *) PAGE_BODY2, "left: 0;" );
	strcat((char *) PAGE_BODY2, "width: 100%;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu {" );
	strcat((char *) PAGE_BODY2, "position: fixed;" );
	strcat((char *) PAGE_BODY2, "height: 100%;" );
	strcat((char *) PAGE_BODY2, "background-color: #191818;" );
	strcat((char *) PAGE_BODY2, "width: 150px;" );
	strcat((char *) PAGE_BODY2, "left: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu {}" );
	strcat((char *) PAGE_BODY2, "#menu ul{" );
	strcat((char *) PAGE_BODY2, "list-style-type: none;" );
	strcat((char *) PAGE_BODY2, "padding: 0;" );
	strcat((char *) PAGE_BODY2, "margin: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li {" );
	strcat((char *) PAGE_BODY2, "line-height: 2.9em;" );
	strcat((char *) PAGE_BODY2, "height: 2.9em; " );
	strcat((char *) PAGE_BODY2, "transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "-moz-transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "-webkit-transition: all 1s;" );
	strcat((char *) PAGE_BODY2, "position: relative;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li a {" );
	strcat((char *) PAGE_BODY2, "display: block;" );
	strcat((char *) PAGE_BODY2, "color: #fff;" );
	strcat((char *) PAGE_BODY2, "padding: 0 1em;" );
	strcat((char *) PAGE_BODY2, "border-bottom: 1px solid #333;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li:hover {" );
	strcat((char *) PAGE_BODY2, "background-color: #454545;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu .sub-menu {" );
	strcat((char *) PAGE_BODY2, "display: none;" );
	strcat((char *) PAGE_BODY2, "position: absolute;" );
	strcat((char *) PAGE_BODY2, "top: 0;" );
	strcat((char *) PAGE_BODY2, "left: 150px;" );
	strcat((char *) PAGE_BODY2, "background-color: #191818;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#menu ul li:hover .sub-menu{" );
	strcat((char *) PAGE_BODY2, "display: block;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#content {" );
	strcat((char *) PAGE_BODY2, "padding: 1em 8em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#header, .call-to-action {" );
	strcat((char *) PAGE_BODY2, "text-align:  center;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "#header {}" );
	strcat((char *) PAGE_BODY2, "#header #logo {font-size:40px;}" );
	strcat((char *) PAGE_BODY2, "#header #slogan {" );
	strcat((char *) PAGE_BODY2, "color: 8997a0;" );
	strcat((char *) PAGE_BODY2, "font-size: 0.8em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".call-to-action {" );
	strcat((char *) PAGE_BODY2, "padding: 1.5em 20%;" );
	strcat((char *) PAGE_BODY2, "background-color: #f0ffff;" );
	strcat((char *) PAGE_BODY2, "border: 1px solid #e8e8e8;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row {" );
	strcat((char *) PAGE_BODY2, "overflow: hidden;" );
	strcat((char *) PAGE_BODY2, "margin: 1.5em auto;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col {" );
	strcat((char *) PAGE_BODY2, "float: left;" );
	strcat((char *) PAGE_BODY2, "width: 40%;" );
	strcat((char *) PAGE_BODY2, "margin: 2em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col:last-child {" );
	strcat((char *) PAGE_BODY2, "float: right;" );
	strcat((char *) PAGE_BODY2, "margin-right: 0;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, ".row .col img {" );
	strcat((char *) PAGE_BODY2, "float: left;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "" );
	strcat((char *) PAGE_BODY2, "#footer {" );
	strcat((char *) PAGE_BODY2, "font-size: 85%;" );
	strcat((char *) PAGE_BODY2, "border-top: 1px solid #e6e6e6;" );
	strcat((char *) PAGE_BODY2, "color: #838383;" );
	strcat((char *) PAGE_BODY2, "padding: 1em 3em;" );
	strcat((char *) PAGE_BODY2, "}" );
	strcat((char *) PAGE_BODY2, "input[type=text], select {width: 180px;padding: 12px 20px; margin: 8px 5px 0 0; \
															display: inline-block;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box;}" );
	strcat((char *) PAGE_BODY2, "input[type=submit] {width: 80px;background-color: #4CAF50;color: white; \
                           		padding: 14px 20px;margin: 8px 0;border: none;border-radius: 4px;cursor: pointer;}" );
	strcat((char *) PAGE_BODY2, "input[type=submit]:hover {background-color: #45a049;}" );
	
	strcat((char *) PAGE_BODY2, "</style>" );
	strcat((char *) PAGE_BODY2, " </head>" );
	strcat((char *) PAGE_BODY2, " <body>" );
	strcat((char *) PAGE_BODY2, " <div id=\"container\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"menu\">" );
	strcat((char *) PAGE_BODY2, " <ul>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"/control\">Homepage</a></li>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"/setting\">Settings</a></li>" );
	//strcat((char *) PAGE_BODY2, " <li><a href=\"#\">LED</a></li>" );
	strcat((char *) PAGE_BODY2, " <li><a href=\"#\">About</a></li>" );
	strcat((char *) PAGE_BODY2, " </ul>" );
	strcat((char *) PAGE_BODY2, " </div><!menu>" );
	strcat((char *) PAGE_BODY2, " <div id=\"content\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"header\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"logo\">WebServer for LCD water control</div>" );
	strcat((char *) PAGE_BODY2, " <div id=\"slogan\">" );
	strcat((char *) PAGE_BODY2, " <p>Web control demo for STM32F4xx</p>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div><!header>" );
	strcat((char *) PAGE_BODY2, " <div class=\"call-to-action\">" );
	strcat((char *) PAGE_BODY2, " <h3>LCD water control via website</h3>" );
	strcat((char *) PAGE_BODY2, " <p>pH and CHL control</p>" );
	strcat((char *) PAGE_BODY2, " </div><!call-to-action>" );
	strcat((char *) PAGE_BODY2, " <div class=\"row\" id=\"intro\">" );
	strcat((char *) PAGE_BODY2, " <div id=\"box1\" class=\"col\">" );
/* Region for Setting form */
	
	strcat((char *) PAGE_BODY2, "<div style=\"padding:10px;border:2px solid;background: azure;border-radius: 5px; text-align:center;margin-bottom: 7px;\">pH settings</div>");
  strcat((char *) PAGE_BODY2, "<form action=\"/phvalue\" method=\"GET\">" );
  strcat((char *) PAGE_BODY2, " <input type=\"text\" id=\"fname\" name=\"ph_min\" placeholder=\"Min value ...\" required>" );
	strcat((char *) PAGE_BODY2, " <input type=\"text\" id=\"fname\" name=\"ph_max\" placeholder=\"Max value ...\" required>" );
  strcat((char *) PAGE_BODY2, " <input type=\"submit\" value=\"Submit\">" );
	strcat((char *) PAGE_BODY2, "</form>" );
	strcat((char *) PAGE_BODY2, "<p><strong>Note</strong>: Please enter the pH value between 0.0 and 14.0</p>");
/* Region for Setting reading */
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " <div id=\"box2\" class=\"col\">" );
/* Region for ADC reading */
	strcat((char *) PAGE_BODY2, "<div style=\"padding:10px;border:2px solid;background: azure;border-radius: 5px; text-align:center;margin-bottom: 7px;\">CL settings</div>");
  strcat((char *) PAGE_BODY2, "<form action=\"/clvalue\" method=\"GET\">" );
  strcat((char *) PAGE_BODY2, " <input type=\"text\" id=\"fname\" name=\"cl_min\" placeholder=\"Min value ...\" required>" );
	strcat((char *) PAGE_BODY2, " <input type=\"text\" id=\"fname\" name=\"cl_max\" placeholder=\"Max value ...\" required>" );
  strcat((char *) PAGE_BODY2, " <input type=\"submit\" value=\"Submit\">" );
	strcat((char *) PAGE_BODY2, "</form>" );	
	strcat((char *) PAGE_BODY2, "<p><strong>Note</strong>: Please enter the CL value between 0.0 and 1.0</p>");
/* Region for ADC reading */
	strcat((char *) PAGE_BODY2, " </div>" );

	strcat((char *) PAGE_BODY2, " </div><!row>" );
	strcat((char *) PAGE_BODY2, " <div id=\"footer\">" );
	strcat((char *) PAGE_BODY2, " <p>Copyright &copy; Le Nhat Thanh</p>" );
	strcat((char *) PAGE_BODY2, " </div>" );
	strcat((char *) PAGE_BODY2, " </div><!content>" );
	strcat((char *) PAGE_BODY2, " </div><!container>" );
	strcat((char *) PAGE_BODY2, " </body>" );
	strcat((char *) PAGE_BODY2, " </html>" );

  write(conn, PAGE_BODY2, strlen(PAGE_BODY2));
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/