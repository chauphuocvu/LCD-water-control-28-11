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
#include "Sensor.h"
//#include "tm_stm32_ds18b20.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*--------------- LCD Messages ---------------*/
#define MESSAGE1   "     STM32F4x7      "
#define MESSAGE2   "  STM32F-4 Series   "
#define MESSAGE3   "Basic WebServer Demo"
#define MESSAGE4   "                    "

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t PrescalerValue = 0;
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD	0xBE	
/*--------------- Tasks Priority -------------*/
#define DHCP_TASK_PRIO   ( tskIDLE_PRIORITY + 2 )      
#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 1 )




/* Private function prototypes -----------------------------------------------*/
void GPIO_Config(void);
void LCDTask(void * pvParameters);
void ActuatorTask(void * pvParameters);
void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName );
void vApplicationTickHook( void );
void Clock(void * pvParameters);
void Read_pH_ORP(void * pvParameters);


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
extern int8_t   	RequireValueDosepH_DoseHour_Display;
extern int8_t 		RequireValueDosepH_DoseDay_Display;
extern uint16_t 	PoolVolume_Display;
extern uint16_t 	FiltrationPeriod_Display;
extern uint16_t 	CalibrationAir_Display;
extern uint16_t 	CalibrationWater_Display;
extern uint16_t 	RequireValueRedoxpH_Redox_Display;
extern float 	 		Probe_pH_Display;
extern float 	 		Probe_CLF_Display;
extern float 	 		RequireValuepH_Display;
extern float 	 		RequireValueCLF_Display;
float pH_read;
float ORP_read;
float pH_V_read;
float V_pH, V_Clo;
float V_step = 0.001;  // litter
uint32_t step_pH,step_Clo;

/* Private functions ---------------------------------------------------------*/
unsigned int temp;
void DS18B20_Write1();
void DS18B20_Write0();
void DS18B20_Write_Bit(unsigned char b);
unsigned char DS18B20_Read_Bit();
void DS18B20_Write_Byte(unsigned char b);
unsigned char DS18B20_Read_Byte();
unsigned char DS18B20_Reset();
void d_us(uint16_t time);
uint16_t counter_delay_us;
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
	ActuatorConfig();
//	ADC_Config();
//  readCalibrationValue();
//	/*Read value set before*/
//	ReadSavedValue();	
//	Show_StartScreen();
//  /* Configure Ethernet (GPIOs, clocks, MAC, DMA) */ 
//  ETH_BSP_Config();
//    
//  /* Initilaize the LwIP stack */
//  LwIP_Init();	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
//  /* Initialize webserver demo */
//  http_server_socket_init();
//	/* Initialize http client demo */
//	//http_client_socket_init();
	
	/************************************************************/
	Interrupts_Config();
   GPIO_InitTypeDef  GPIO_InitStructure;
  /* GPIOG Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  /* Configure in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
#ifdef USE_DHCP
  /* Start DHCPClient */
  xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
#endif
    
//	xTaskCreate(LCDTask, "LCDTask", configMINIMAL_STACK_SIZE*12, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(ActuatorTask, "ActuatorTask", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);
//	xTaskCreate(Clock, "Clock", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
		xTaskCreate(Read_pH_ORP, "Read_pH_ORP", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);

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
Chau phuoc vu 18/4/2019
  */
void Read_pH_ORP(void * pvParameters)
{
  for ( ;; ) {		
	pH_V_read = (GetMiliVoltage(pHSensor)/1000 - 1.611)/(-5.504464286);
	pH_read = 7 - (pH_V_read - 0.0005)/slope_pH(30);
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
			if (step_Clo < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_RX);
				step_Clo++;
			}
			if (step_pH < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_PH);
				step_pH++ ;
			}
			vTaskDelay(3);
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
			vTaskDelay(3);
		break;
		case START_STOP	 :
			if (step_Clo < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_RX);
				step_Clo++;
			}
			vTaskDelay(3);
			ControlActuator(OFF,GPIOA, PUMP_RX);
			vTaskDelay(3);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		case STOP_START	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			if (step_pH < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_PH);
				step_pH++ ;
			}
			vTaskDelay(3);
			ControlActuator(OFF,GPIOA, PUMP_PH);
			vTaskDelay(3);
		break;
		case STOP_STOP	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		default :
		break;			
	}		
//while(DS18B20_Reset()){;}
//		DS18B20_Write_Byte(DS18B20_SKIP_ROM);
//		DS18B20_Write_Byte(DS18B20_CONVERT_T);

//		vTaskDelay(750);

//		while(DS18B20_Reset());
//		DS18B20_Write_Byte(DS18B20_SKIP_ROM);
//		DS18B20_Write_Byte(DS18B20_READ_SCRATCHPAD);

//		temp = DS18B20_Read_Byte();
//		temp = (DS18B20_Read_Byte() << 8) | temp;
	DS18B20_Reset();

}
}
/**
  * @brief  My task
  * @param  pvParameters not used
  * @retval None
  */
void Clock(void * pvParameters)
{
  for ( ;; ) {
	sec=sec+1;
	if(sec>59) {min=min+1; sec=0; } 
  if(min>59) { hour=hour+1; min=0; } 
  if(hour>23) { hour=0; min=0; sec=0; }
	vTaskDelay(1000);
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
// Return 0: Ok
// Return 1: FAIL
unsigned char DS18B20_Reset()
{
	unsigned char result;

	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	d_us(480);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	d_us(70);
	
	result = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);

	d_us(410);

	return result;
}
void DS18B20_Write1()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	d_us(6);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	d_us(64);
}

void DS18B20_Write0()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	d_us(60);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	d_us(10);	
}

void DS18B20_Write_Bit(unsigned char b)
{
	if(b == 1)
	{
	 	DS18B20_Write1();
	}
	else
	{
	 	DS18B20_Write0();
	}
}

unsigned char DS18B20_Read_Bit()
{
	unsigned char result;

	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	d_us(6);

	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	d_us(9);

	result = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
	d_us(55);

	return result;
}

void DS18B20_Write_Byte(unsigned char b)
{
 	unsigned char i = 8;

	while(i--)
	{
		DS18B20_Write_Bit(b & 0x01);
		b >>= 1;
	}
}

unsigned char DS18B20_Read_Byte()
{
 	unsigned char i = 8, result = 0;

	while(i--)
	{
		result >>= 1;
		result |= (DS18B20_Read_Bit()<<7);		
	}
   	
	return result;
}



//void d_us(uint16_t time)
//{
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//  
//  /* Time base configuration */
//  TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;     // frequency = 1000000
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_Period = 10-1;
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	TIM_SetCounter(TIM4,0);
//	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
//	TIM_Cmd(TIM4, ENABLE);
//	while(time--)
//	{
//		while(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update) == 0);
//		TIM_ClearFlag(TIM4,TIM_FLAG_Update);
//	}
//	TIM_Cmd(TIM4, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);
//}
static void TimerDelay_us_Config( void )
{
	// Enable clock for TIM5
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = TIMER_US_DELAY_PERIOD;      
	TIM_TimeBaseStructure.TIM_Prescaler = TIMER_US_DELAY_PRESCALER;       
	TIM_TimeBaseStructure.TIM_ClockDivision 	= TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode 		= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMER_US_DELAY, &TIM_TimeBaseStructure);
	
	TIM_UpdateRequestConfig(TIMER_US_DELAY, TIM_UpdateSource_Global);
	
	TIM_ClearITPendingBit(TIMER_US_DELAY, TIM_IT_Update);
		
	/* Enable TIMER Update interrupt */
	TIM_ITConfig(TIMER_US_DELAY, TIM_IT_Update, ENABLE);

	/* Disable timer	*/
	TIM_Cmd(TIMER_US_DELAY, DISABLE);
}
void d_us(uint16_t delay)
{
	counter_delay_us = delay;
	
	TimerDelay_us_Config ();

	TIM_SetCounter(TIMER_US_DELAY, 0);
	/* TIM2 enable counter */
	TIM_Cmd(TIMER_US_DELAY, ENABLE);
	/* Wait for 'delay' us */
	while(counter_delay_us != 0);
	/* TIM2 disable counter */
	TIM_Cmd(TIMER_US_DELAY, DISABLE);
}