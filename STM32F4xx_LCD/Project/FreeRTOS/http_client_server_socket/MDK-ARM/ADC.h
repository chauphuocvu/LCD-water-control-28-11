/*			CHAU PHUOC VU				*/


#include "stm32f4xx_adc.h"
#include "stm32f4xx_uartstdio.h"

#define ADC1_DR_ADDRESS			0x4001204C
#define pHSensor		ADC_Channel_0
#define RedoxSensor	ADC_Channel_6
#define TempSensor	ADC_Channel_8
#define ProxSensor 	ADC_Channel_9




extern __IO uint16_t ADC1ConvertedValue;
extern __IO float ADC1ConvertedVoltage;



float GetMiliVoltage(uint8_t Sensor);
/* ADC1 init function */
void ADC_Config(void);

