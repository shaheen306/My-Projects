/*
 * BUTTON.c
 *
 * Created: 4/8/2020 10:51:33 PM
 *  Author: Shaheen
 */ 
#define F_CPU 8000000
#include <util/delay.h>
#include "GPIO_MCAL.h"
void BUTTON_INIT(u8 port,u8 pinnum){
	GPIO_SETPIN_DIR(port,pinnum,0);
	
}
u8 BUTTON_READ(u8 port,u8 pinnum){
	u8 x=0;
	x=GPIO_READ_PIN(port,pinnum);
	_delay_ms(5);
	x=GPIO_READ_PIN(port,pinnum);
	return x;
}
