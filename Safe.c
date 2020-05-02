/*
 * Safe.c
 *
 * Created: 5/1/2020 6:41:37 PM
 *  Author: Shaheen
 */ 
#define F_CPU 8000000UL
#include "GPIO_MCAL.h"
#include "LCD.h"
#include "Datatypes.h"
#include "EEPROM.h"
#include "KEYPAD.h"
#include "LED.h"
#include <util/delay.h>
#define TRIES 3
int main(void)
{
	enum{
		EEPROM_STATUS_LOC=0x10,
		EEPROM_PASS_LOC1,
		EEPROM_PASS_LOC2,
		EEPROM_PASS_LOC3,
		EEPROM_PASS_LOC4
		};
	LED_INIT('C',0);
	LED_INIT('C',1);
	u16 location[4]={EEPROM_PASS_LOC1,EEPROM_PASS_LOC2,EEPROM_PASS_LOC3,EEPROM_PASS_LOC4};
	u8 pass[4];	
	LCD_GET_CONFIG(FOUR_BIT,LOW_NIBBLE,'A','B',0,'B',1,'B',2);
	LCD_INIT();
	KEYPAD_INIT('D');
	u8 val=NOTPRESSED;
	u8 flag=0;
	u8 i,j;
	u8 max=TRIES;

	if(EEPROM_READ(EEPROM_STATUS_LOC)==NOTPRESSED){
		LCD_SEND_STRING("Set Pass:");
		for(i=0;i<4;i++){
			do
			{
				val=KEYPAD_CKECK_PRESS('D');
			} while (val==NOTPRESSED);
			LCD_SEND_CHAR(val);
			_delay_ms(100);
			LCD_MOVE_CURSOR(1,(i+10));
			LCD_SEND_CHAR('*');
			_delay_ms(100);
			EEPROM_WRITE(location[i],val);
			val=NOTPRESSED;	
			}		
			_delay_ms(100);
			EEPROM_WRITE(EEPROM_STATUS_LOC,0x00);
			
						
	}
	
	
	while(flag==0){
		pass[0]=pass[1]=pass[2]=pass[3]=NOTPRESSED;
		LCD_clear_screen();
		LCD_SEND_STRING("Enter pass:");
		for (j=0;j<4;j++)
		{
			do 
			{
				pass[j]=KEYPAD_CKECK_PRESS('D');
			} while (pass[j]==NOTPRESSED);
			LCD_SEND_CHAR(pass[j]);
			_delay_ms(100);
			LCD_MOVE_CURSOR(1,(j+12));
			LCD_SEND_CHAR('*');
			_delay_ms(100);
		}
		if(pass[0]==EEPROM_READ(location[0]) && pass[1]==EEPROM_READ(location[1]) && pass[2]==EEPROM_READ(location[2])&& pass[3]==EEPROM_READ(location[3])){
			LCD_clear_screen();
			LCD_SEND_STRING("Right pass!");
			_delay_ms(500);
			LCD_MOVE_CURSOR(2,1);
			LCD_SEND_STRING("Safe is opened");
			LED_ON('C',0);
			flag=1;
		}else{
			max-=1;
			if (max!=0)
			{
				LED_ON('C',1);
				LCD_clear_screen();
				LCD_SEND_STRING("Wrong password");
				_delay_ms(300);
				LCD_MOVE_CURSOR(2,1);
				LCD_SEND_STRING("Tries left:");
				LCD_DISP_NUMBER(max);
				_delay_ms(300);
				LED_OFF('C',1);
				
			}else{
				LCD_clear_screen();
				LCD_SEND_STRING("Access denied");
				_delay_ms(500);
				LCD_MOVE_CURSOR(2,1);
				LCD_SEND_STRING("Safe is closed");
				while(1){
					LED_TOGGLE('C',1);
					_delay_ms(50);
				}
				
				
				break;
			}
		}					
	}	
	
	
    while(1)
    {
        
    }
}