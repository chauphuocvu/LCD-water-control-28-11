/*						CHAU PHUOC VU					*/



#include "Actuator.h"


void ActuatorConfig(void)
{
	/* Private typedef -----------------------------------------------------------*/
	GPIO_InitTypeDef  GPIO_InitStructure;
  /* GPIOG Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Configure in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = PUMP_PH | PUMP_RX;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}




void ControlActuator(uint8_t Status, GPIO_TypeDef* GPIOx, uint8_t Type)
{
	switch(Status)
	{
		case ON :
			GPIOx->BSRRL = Type;
		break;
		case OFF :
			GPIOx->BSRRH = Type;
		break;
		default :
		break;
	}
}
