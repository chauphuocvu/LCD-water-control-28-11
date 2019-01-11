/*			CHAU PHUOC VU				*/


#include "stm32f4xx_adc.h"

#define ADC1_DR_ADDRESS			0x4001204C


extern __IO uint16_t ADC1ConvertedValue;
extern __IO uint32_t ADC1ConvertedVoltage;