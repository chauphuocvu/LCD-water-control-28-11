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
#include <stdlib.h>
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
#define ADC_TASK_PRIO			( tskIDLE_PRIORITY + 1 )


//ReaderConfigStruct					ReaderConfig;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void GPIO_Config(void);
void ADC_Config(void);
uint16_t ADC_Read(uint8_t);
void TestTask(void * pvParameters);
void ADCTask(void * pvParameters);
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName );
void vApplicationTickHook( void );

volatile uint16_t ADC_value;
volatile uint16_t CL_ADC_value;
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
	ADC_Config();
	
  readCalibrationValue();

  GL_SetTextColor(BLUE);
  GL_SetBackColor(MAGENTA);
  GL_Clear(WHITE);
	
	//ADC_value = ADC_Read(ADC_Channel_0);
  Show_HomeScreen();

  /* Configure Ethernet (GPIOs, clocks, MAC, DMA) */ 
	ETH_BSP_Config();
    
  /* Initilaize the LwIP stack */
  LwIP_Init();
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
  /* Initialize webserver demo */
  http_server_socket_init();
	/* Initialize http client demo */
//	http_client_socket_init();
	
#ifdef USE_DHCP
  /* Start DHCPClient */
  xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
#endif

  /* Start toogleLed4 task : Toggle LED4  every 250ms */
  xTaskCreate(TestTask, "Test", configMINIMAL_STACK_SIZE*12, NULL, LED_TASK_PRIO, NULL);
//  
	xTaskCreate(ADCTask, "ADC_task", configMINIMAL_STACK_SIZE, NULL, ADC_TASK_PRIO, NULL);
	
  /* Start scheduler */
  vTaskStartScheduler();
  /* We should never get here as control is now taken by the scheduler */
  for ( ;; );
}

void ADCTask(void * pvParameters)
{
  for ( ;; ) 
	{
			// pH code here
		ADC_value = ADC_Read(ADC_Channel_0);
		if(CurrentScreen == &home_screen)
		{
			// Convert ADC value to PH value with: PH_value = 14 * ADC_value / 4096
			int PH_value = 14 * ADC_value / 4096;
			
			int PH_value_r = (14 * ADC_value) % 4096;
			float PH_value_r_float = (float)PH_value_r / (float)4096;
			PH_value_r = (int)(PH_value_r_float * 10);
			char array[6] = {(PH_value / 10) + 48, (PH_value % 10) + 48, ',', PH_value_r + 48, 'p', 'H'};
			char* string = array;
			
			LCD_DrawFullRect(305, 120, 100, 50, RGB565CONVERT(0, 159, 227));
			GL_DisplayAdjStringLine(120, 305, string, TRUE);
			
			
			// CHLORINE
			CL_ADC_value = ADC_Read(ADC_Channel_6);
			// Convert ADC value to PH value with: CL_value = 1 * ADC_value / 4096
			int CL_value = 1 * CL_ADC_value / 4096;
			
			float CL_value_r_float = (float)CL_ADC_value / (float)4096;
			int CL_value_r = (int)(CL_value_r_float * 10);
			int CL_value_r_100 = (int)(CL_value_r_float * 100) - CL_value_r * 10;
			char array2[5] = {'0', ',', CL_value_r + 48, CL_value_r_100 + 48, '\0'};
			char* string2 = array2;
			LCD_DrawFullRect(90, 120, 100, 50, 52804);
			GL_DisplayAdjStringLine(120, 90, string2, TRUE);
			
		}
		vTaskDelay(1000);
  }
}


/**
  * @brief  Test task
  * @param  pvParameters not used
  * @retval None
  */
void TestTask(void * pvParameters)
{
  for ( ;; ) {
		getTouchPoint();

		ProcessInputData();
		/* Time out calculate for power saving mode */
    TimeOutCalculate();
		
//		touch_done = 0;
		vTaskDelay(100);
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

void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_DeInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// init GPIO PA0 in INPUT mode for ADC
	GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_CommonInitTypeDef     ADC_CommonInitStructure;
		ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
		ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
		ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_NbrOfConversion = 2;
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b; //Input voltage is converted into a 12bit number giving a maximum value of 4096
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;

	ADC_Init(ADC1, &ADC_InitStruct);
	
  ADC_Cmd(ADC1, ENABLE);
    
}

uint16_t ADC_Read(uint8_t channel)
{
	// ADC1 channel 0 is on PA0
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_84Cycles);
	// Start ADC conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion is finish
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

  return ADC_GetConversionValue(ADC1);
	//------------- END ADC ----------------------
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
	UARTprintf("freeHeapsize = %d\n",xPortGetFreeHeapSize());
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
