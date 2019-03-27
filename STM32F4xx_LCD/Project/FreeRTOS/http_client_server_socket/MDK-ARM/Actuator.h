/*						CHAU PHUOC VU					*/
#include "stm32f4xx.h"

#define PUMP_PH				GPIO_Pin_5
#define PUMP_RX				GPIO_Pin_4
#define ON						1
#define OFF						0


void ControlActuator(uint8_t Status, GPIO_TypeDef* GPIOx, uint8_t Type);
void ActuatorConfig(void);
