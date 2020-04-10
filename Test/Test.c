/*
 * Test.c
 *
 * Created: 4/9/2020 7:05:49 AM
 *  Author: Shaheen
 */ 

#define F_CPU 8000000UL
#include "GPIO_MCAL.h"
#include "LED.h"
#include <util/delay.h>


int main(void)
{
	LED_INIT('A',0);
	LED_INIT('A',1);
	LED_INIT('A',2);
	u8 counter=0;
    while(1)
    {	
		for(counter;;counter++){
			if(counter%2==1){
				LED_OFF('A',1);
				LED_OFF('A',2);
				LED_ON('A',0);
				_delay_ms(500);
				
			}else{
				LED_OFF('A',0);
				if(counter%3==2){
					LED_ON('A',1);
					_delay_ms(500);
					
				}else{
					LED_OFF('A',1);
					if(counter%4==3){
						LED_ON('A',1);
						_delay_ms(500);
					}else{
						LED_OFF('A',0);
						LED_OFF('A',1);
						LED_OFF('A',2);
						_delay_ms(500);
					}
				}
			}
			if((counter%2==1)&&(counter%3==2)){
				LED_ON('A',0);
				LED_ON('A',1);
				_delay_ms(500);
			}else if((counter%2==1)&&(counter%4==3)){
				LED_ON('A',0);
				LED_ON('A',2);
				_delay_ms(500);
			}else{
				
			}
			if((counter%2==1)&&(counter%3==2)&&(counter%4==3)){
				LED_ON('A',0);
				LED_ON('A',1);
				LED_ON('A',2);
				_delay_ms(500);
				
			}else{
				
			}
			
		}
	
	}
}