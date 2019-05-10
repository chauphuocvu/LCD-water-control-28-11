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
#include "ds18b20_mflib.h"

/* Private define ------------------------------------------------------------*/

/*--------------- LCD Messages ---------------*/
#define MESSAGE1   "     STM32F4x7      "
#define MESSAGE2   "  STM32F-4 Series   "
#define MESSAGE3   "Basic WebServer Demo"
#define MESSAGE4   "                    "

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t PrescalerValue = 0;

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
/*chau phuoc vu 23/4/2019*/
float RX_V_read;
float Volume_pH, Volume_Clo;
float V_step = 0.1;  // ml
uint32_t step_pH,step_Clo;
float pH_V_calibration = 0.0005;
/* Private functions ---------------------------------------------------------*/
unsigned int temp;
void DelayMicro(uint16_t delay);
volatile uint16_t counter_delay_us;
static void TimerDelay_us_Config( void );
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
	ADC_Config();
  readCalibrationValue();
	/*Read value set before*/
	ReadSavedValue();	
	Show_StartScreen();
  /* Configure Ethernet (GPIOs, clocks, MAC, DMA) */ 
  ETH_BSP_Config();
    
  /* Initilaize the LwIP stack */
  LwIP_Init();	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
  /* Initialize webserver demo */
  http_server_socket_init();
	/* Initialize http client demo */
	//http_client_socket_init();
//	
////	/************************************************************/
//	Interrupts_Config();

//	TimerDelay_us_Config();
//    
#ifdef USE_DHCP
  /* Start DHCPClient */
  xTaskCreate(LwIP_DHCP_task, "DHCPClient", configMINIMAL_STACK_SIZE * 2, NULL,DHCP_TASK_PRIO, NULL);
#endif
//    
	xTaskCreate(LCDTask, "LCDTask", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(ActuatorTask, "ActuatorTask", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate(Clock, "Clock", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
//  xTaskCreate(Read_pH_ORP, "Read_pH_ORP", configMINIMAL_STACK_SIZE*2, NULL, LED_TASK_PRIO, NULL);

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
/**
Chau phuoc vu 23/4/2019
  */
	pH_V_read = (GetMiliVoltage(pHSensor)/1000 - 1.611)/(-5.504464286);
	pH_read = Probe_pH - (pH_V_read - pH_V_calibration)/slope_pH(25);
	/* chau phuoc vu 25/4/2019*/
	RX_V_read = (/*GetMiliVoltage(ORPSensor)*/1149/1000 - 0.0741)/(2.31733631);
	if (Calibration_pH_Flag == NO_CALIBRATION_PH)
	{
		Probe_pH_Display = pH_read;
	}
	/* chau phuoc vu 27/4/2019*/
	if (Calibration_Rx_Flag == NO_CALIBRATION_RX)
	{
		Probe_CLF_Display = RX_V_read;
	}
	vTaskDelay(200);
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
		case STOP_STOP :
			if (step_Clo < 4000)
			{
				ControlActuator(ON,GPIOA, PUMP_RX);
				step_Clo++;
			}
			if (step_pH < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_PH);
				step_pH++ ;
			}
			vTaskDelay(1);
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
			vTaskDelay(3);
		break;
		case 	STOP_START :
			if (step_Clo < 4000)
			{
				ControlActuator(ON,GPIOA, PUMP_RX);
				step_Clo++;
			}
			vTaskDelay(1);
			ControlActuator(OFF,GPIOA, PUMP_RX);
			vTaskDelay(3);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		case START_STOP	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			if (step_pH < 2000)
			{
				ControlActuator(ON,GPIOA, PUMP_PH);
				step_pH++ ;
			}
			vTaskDelay(1);
			ControlActuator(OFF,GPIOA, PUMP_PH);
			vTaskDelay(3);
		break;
		case START_START	 :
			ControlActuator(OFF,GPIOA, PUMP_RX);
			ControlActuator(OFF,GPIOA, PUMP_PH);
		break;
		default :
		break;			
	}		
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
//	ds18b20_init_seq();
//	ds18b20_send_rom_cmd(SKIP_ROM_CMD_BYTE);
//	ds18b20_send_function_cmd(CONVERT_T_CMD);
// 	DelayMicro(100);
//	ds18b20_init_seq();
//	ds18b20_send_rom_cmd(SKIP_ROM_CMD_BYTE);
//	ds18b20_send_function_cmd(READ_SCRATCHPAD_CMD);
//	temp = ds18b20_read_temp();	// returns float value
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
//	   GPIO_InitTypeDef  GPIO_InitStructure;
//  /* GPIOG Peripheral clock enable */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//  /* Configure in output pushpull mode */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
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
void DelayMicro(uint16_t delay)
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
