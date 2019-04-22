/*						CHAU PHUOC VU					*/
#include "ADC.h"




/* You can monitor the converted value by adding the variable "ADC1ConvertedValue" 
   to the debugger watch window */
__IO uint16_t ADC1ConvertedValue;
__IO float ADC1ConvertedmV = 0;

/* ADC1 init function */
void ADC_Config(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
	/* Enable ADCx, DMA and GPIO clocks ****************************************/ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* Configure the GPIOB pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* Configure the GPIOA pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	 /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
	ADC_DeInit();
	/* Configure ADC_InitStructure */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
}



float GetMiliVoltage(uint8_t Sensor)
{
	ADC_RegularChannelConfig(ADC1, Sensor, 1, ADC_SampleTime_84Cycles);
	// Start ADC conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion is finish
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	//Convert to mili Voltage
	ADC1ConvertedmV = ADC_GetConversionValue(ADC1)*3300/4095;
//	UARTprintf("%d\r\n",ADC1ConvertedmV);
	return ADC1ConvertedmV;
}
