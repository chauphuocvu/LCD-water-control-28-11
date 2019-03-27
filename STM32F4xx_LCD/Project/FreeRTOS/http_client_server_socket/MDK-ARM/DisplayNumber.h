/*
			CHAU PHUOC VU
*/

#include "stm32f4_discovery_LCD_SSD1963.h"
#include "uiframework.h"
#include "uiappuser.h"

#define None	0
#define Time	1
#define pH		2
#define ml		3
#define m3		4
#define h			5
#define mgl		6
#define mgh		7
#define mV		8
#define oC		9

extern uint8_t hour;
extern uint8_t min;
extern uint8_t sec;
void DisplayNumber(void);


/*****************hien thi so interger va don vi di kem********************************/
void DisplayIntegerNumber(uint16_t line, uint16_t column, uint16_t value, uint8_t quantity, uint8_t unit);


//ham tinh luy thua
uint16_t power(uint16_t number, uint16_t n);


/*****************hien thi so double va don vi di kem********************************/
void DisplayDoubleNumber(uint16_t line, uint16_t column, double value, uint8_t natural, uint8_t decimal, uint8_t unit);
