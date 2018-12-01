/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Main program body
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
  * <h2><center>&copy; Portions COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
/**
  ******************************************************************************
  * <h2><center>&copy; Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    main.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   Main program body      
  *          Modified to support the STM32F4DISCOVERY, STM32F4DIS-BB and
  *          STM32F4DIS-LCD modules. 
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */  
/* Includes ------------------------------------------------------------------*/
#include "stm32f4x7_eth.h"
#include "netconf.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tcpip.h"
#include "httpserver-socket.h"
#include "httpclient-socket.h"
#include "stm32f4xx_uartstdio.h"
#include "stm32f4_discovery_LCD_SSD1963.h"
#include "SSD1963_CMD.h"
#include "stm32f4_discovery_tsc2046.h"
//#include "rfid_reader.h"
#include "uiframework.h"
#include "LcdHal.h"
/////////////////////////////////////
#include "uiappuser.h"
#include "flash_memory_driver.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*--------------- LCD Messages ---------------*/
#define MESSAGE1   "     STM32F4x7      "
#define MESSAGE2   "  STM32F-4 Series   "
#define MESSAGE3   "Basic WebServer Demo"
#define MESSAGE4   "                    "

/*--------------- Tasks Priority -------------*/
#define DHCP_TASK_PRIO   ( tskIDLE_PRIORITY + 2 )      
#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 1 )

//ReaderConfigStruct					ReaderConfig;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void GPIO_Config(void);
void MyTask(void * pvParameters);
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName );
void DisplayArgument(void);
void CreateTask2(void * pvParameters);
void vApplicationTickHook( void );
uint16_t datar = 0;
extern uint16_t		Screen;
extern uint16_t PoolSelect;
extern uint16_t Temperature;
extern uint16_t WaterHardnessSelect;
extern uint16_t PoolVolume;
extern uint16_t FiltrationPeriod;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured to 
       144 MHz, this is done through SystemInit() function which is called from
       startup file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */  
//	SystemInit();
	UARTstdio_Configuration(USART1,115200);
  GPIO_Config();
	STM324xG_LCD_Init();
	GL_SetFont(GL_FONT_BIG);
	TP_Init();
  readCalibrationValue();
	/*Read value set before*/
	PoolSelect = ReadDataFromFlashForSelect(FLASH_ADDR_POOL_SELECT);
	Temperature = ReadDataFromFlashForSelect(FLASH_ADDR_TEMP_SELECT);
	WaterHardnessSelect = ReadDataFromFlashForSelect(FLASH_ADDR_WATER_HARDNESS_SELECT);
	PoolVolume = ReadDataFromFlashForSelect(FLASH_ADDR_POOL_VOLUME);
	FiltrationPeriod = ReadDataFromFlashForSelect(FLASH_ADDR_FILTRATIONPERIOD);
	
	Show_ParametersRequireValueCLFScreen();
//	Show_StartScreen();

	
  /* Configure Ethernet (GPIOs, clocks, MAC, DMA) */ 
//  ETH_BSP_Config();
    
  /* Initilaize the LwIP stack */
//  LwIP_Init();
	
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
  /* Initialize webserver demo */
//  http_server_socket_init();
	/* Initialize http client demo */
	//http_client_socket_init();
	
#ifdef USE_DHCP
  /* Start DHCPClient */
  xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
#endif
    
  /* Start toogleLed4 task : Toggle LED4  every 250ms */
//	xTaskCreate(CreateTask1, "CreateTask1", configMINIMAL_STACK_SIZE*10, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(MyTask, "MyTask", configMINIMAL_STACK_SIZE*20, NULL, LED_TASK_PRIO, NULL);
 // xTaskCreate(DisplayArgument, "DisplayArgument", configMINIMAL_STACK_SIZE*10, NULL, LED_TASK_PRIO, NULL);

	/* Start scheduler */
  vTaskStartScheduler();
  /* We should never get here as control is now taken by the scheduler */
  for ( ;; );
}

/**
  * @brief  My task
  * @param  pvParameters not used
  * @retval None
  */
void MyTask(void * pvParameters)
{
  for ( ;; ) {
		
		getTouchPoint();
		ProcessInputData();
		/* Time out calculate for power saving mode */
    TimeOutCalculate();	
//		touch_done = 0;
		DisplayArgument();
  }
}
void DisplayArgument(void)
{
		//UARTprintf("co chay Switch case\r\n");
		switch(Screen)
		{
			case StartScreen_df:
				LCD_SetColors(WHITE,BLACK);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(20,130,(uint8_t *)"00:00:01");
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(130,100,(uint8_t *)"0.5");//hien thi Chlorine
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,170,(uint8_t *)"0.5");	
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(130,330,(uint8_t *)"0.5");//hien thi pH
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,400,(uint8_t *)"0.5");		
				break;
			case SettingsScreen_df:
				break;
			case DosingTestStartStartScreen_df:
			case DosingTestStopStartScreen_df:
			case DosingTestStopStopScreen_df:
			case DosingTestStartStopScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(120,100,(uint8_t *)"150");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(70,170,(uint8_t *)"400ml");	
				LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(120,330,(uint8_t *)"150");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");
				LCD_DisplayStringLine(127,385,(uint8_t *)"ml");
				break;
			case ParametersScreen_df:
				break;
			case ParametersPoolVolumeScreen_df:
			case ParametersFitrationPeriodScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,100,(uint8_t *)"15 m3");
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"06 h");
				break;
			case ParametersWaterScreen_df:
				break;
			case WarningMaximalSafetyScreen_df:
				LCD_SetColors(WHITE,VU_GREEN);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(150,195,(uint8_t *)"15");
				break;
			case WarningExtremeConditionScreen_df:
				LCD_SetColors(WHITE,VU_RED);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(150,195,(uint8_t *)"15");
				break;
			case WarningWaterHardnessScreen_df:
				break;
			case WarningProbeCalibration62_78Screen_df:
				break;
			case WarningProbeCalibrationScreen_df:
				break;
			case WarningProbeCalibration70Screen_df:
				break;
			case WarningProbeCalibrationRequiredValueScreen_df:
				break;
			case WarningProbeCalibrationRequiredValueRedScreen_df:
				break;
			case WarningProbeCalibrationRequiredValueImpossibleScreen_df:
				break;
			case WarningTooRapidChangeScreen_df:
				break;
			case ParametersRequireValuepHScreen_df:
			case ParametersRequireValueCLFScreen_df:
				LCD_SetColors(WHITE,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,100,(uint8_t *)"0,2");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,165,(uint8_t *)"mg/l");
				LCD_SetColors(WHITE,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"7,0");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
		}
}
void CreateTask2(void * pvParameters)
{
  for ( ;; ) {
	
  }
}
/**
  * @brief  Initializes the LCD and LEDs resources.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
  STM_EVAL_LEDInit(TP_CS); 
	STM_EVAL_LEDInit(LCD_RST); 
	STM_EVAL_LEDInit(BZ);
	STM_EVAL_LEDInit(LCD_BL);
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
//	UARTprintf("freeHeapsize = %d\n",xPortGetFreeHeapSize());
	for( ;; );
}
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName )
																		{
																		}
void vApplicationTickHook( void )
{
	TimingDelay_Decrement();
	DelayScreen_Decrement();
}
/*********** Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/
