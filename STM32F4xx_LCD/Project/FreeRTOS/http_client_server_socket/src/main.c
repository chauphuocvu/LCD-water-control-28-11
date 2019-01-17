/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Main program body
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
#include "uiframework.h"
#include "LcdHal.h"
#include "uiappuser.h"
#include "flash_memory_driver.h"
#include "DisplayNumber.h"
#include "ADC.h"
#include "Actuator.h"

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




/* Private function prototypes -----------------------------------------------*/
void GPIO_Config(void);
void LCDTask(void * pvParameters);
void ActuatorTask(void * pvParameters);
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName );
void vApplicationTickHook( void );


/* Extern variable -----------------------------------------------*/
extern uint8_t 		Languages_Choose;
extern uint8_t		PoolSelect;
extern uint8_t 		Temperature;
extern uint8_t 		WaterHardnessSelect;
extern uint8_t 		TypeofProbe;
extern uint8_t   	RequireValueDosepH_DoseHour;
extern uint8_t 		RequireValueDosepH_DoseDay;
extern uint16_t 	PoolVolume;
extern uint16_t 	FiltrationPeriod;
extern uint16_t 	CalibrationAir;
extern uint16_t 	CalibrationWater;
extern uint16_t 	RequireValueRedoxpH_Redox;
extern float 	 		Probe_pH;
extern float 	 		Probe_CLF;
extern float 	 		RequireValuepH;
extern float 	 		RequireValueCLF;
extern uint8_t   	RequireValueDosepH_DoseHour_Display;
extern uint8_t 		RequireValueDosepH_DoseDay_Display;
extern uint16_t 	PoolVolume_Display;
extern uint16_t 	FiltrationPeriod_Display;
extern uint16_t 	CalibrationAir_Display;
extern uint16_t 	CalibrationWater_Display;
extern uint16_t 	RequireValueRedoxpH_Redox_Display;
extern float 	 		Probe_pH_Display;
extern float 	 		Probe_CLF_Display;
extern float 	 		RequireValuepH_Display;
extern float 	 		RequireValueCLF_Display;

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
	TP_Init();
	ActuatorConfig();
	ADC_Config();

  readCalibrationValue();
	/*Read value set before*/
	ReadSavedValue();	
	Show_StartScreen();
	
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
    
	xTaskCreate(LCDTask, "LCDTask", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(ActuatorTask, "ActuatorTask", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);

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
void LCDTask(void * pvParameters)
{
  for ( ;; ) {		
		getTouchPoint();
		ProcessInputData();
		/* Time out calculate for power saving mode */
    TimeOutCalculate();	
		DisplayNumber();
}
}

/**
  * @brief  My task
  * @param  pvParameters not used
  * @retval None
  */
void ActuatorTask(void * pvParameters)
{
  for ( ;; ) {	
//Control Pump pH and Clo
	switch(DosingTest_Flag)
	{
		case START_START :
			ControlActuator(ON,GPIOA, PUMP_RX);
			ControlActuator(ON,GPIOA, PUMP_PH);
		break;
		case START_STOP	 :
			ControlActuator(ON,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		case STOP_START	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(ON,GPIOA, PUMP_PH);
		break;
		case STOP_STOP	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		default :
		break;			
	}
		
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
}
/*********** Portions COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE****/
