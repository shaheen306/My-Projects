/*
 * LCD.c
 *
 * Created: 4/10/2020 7:49:43 AM
 *  Author: Shaheen
 */ 
#include "GPIO_MCAL.h"
#include "LCD.h"
#define F_CPU 8000000UL
#include <util//delay.h>

void LCD_INIT(u8 mode,u8 nibble,u8 port,u8 rs_port,u8 rs_pin,u8 rw_port,u8 rw_pin,u8 en_port,u8 en_pin){
	_delay_ms(200);
	GPIO_SETPIN_DIR(rs_port,rs_pin,1);
	GPIO_SETPIN_DIR(rw_port,rw_pin,1);
	GPIO_SETPIN_DIR(en_port,en_pin,1);
	if(mode==1){
		GPIO_SETPORT_DIR(port,0xff);
		GPIO_WRITE_PIN(rw_port,rw_pin,0);
		_delay_ms(15);
		LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_FUNCTION_8BIT_2LINES, en_port, en_pin);
		_delay_ms(1);
		LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_DISP_ON_CURSOR_ON, en_port, en_pin);
		_delay_ms(1);
		LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_CLEAR_SCREEN, en_port, en_pin);
		_delay_ms(10);
		LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_ENTRY_MODE, en_port, en_pin);
		_delay_ms(1);
	}else{
		if(nibble==1){
			GPIO_HIGH_NIBBLE_SETDIR(port,1);
			GPIO_WRITE_PIN(rw_port,rw_pin,0);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_RETURN_HOME, en_port, en_pin);
			_delay_ms(15);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_FUNCTION_4BIT_2LINES, en_port, en_pin);
			_delay_ms(1);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_DISP_ON_CURSOR_ON, en_port, en_pin);
			_delay_ms(1);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_CLEAR_SCREEN, en_port, en_pin);
			_delay_ms(10);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_ENTRY_MODE, en_port, en_pin);
			_delay_ms(1);
		}else{
			GPIO_LOW_NIBBLE_SETDIR(port,1);
			GPIO_WRITE_PIN(rw_port,rw_pin,0);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_RETURN_HOME, en_port, en_pin);
			_delay_ms(15);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_FUNCTION_4BIT_2LINES, en_port, en_pin);
			_delay_ms(1);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_DISP_ON_CURSOR_ON, en_port, en_pin);
			_delay_ms(1);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_CLEAR_SCREEN, en_port, en_pin);
			_delay_ms(10);
			LCD_SEND_CMD( mode, nibble, port, rs_port, rs_pin,LCD_ENTRY_MODE, en_port, en_pin);
			_delay_ms(1);
		}
	}
}
static void ENABLE_SET(u8 en_port,u8 en_pin){
	GPIO_WRITE_PIN(en_port,en_pin,1);
	_delay_ms(2);
	GPIO_WRITE_PIN(en_port,en_pin,0);
}
void LCD_SEND_CMD(u8 mode,u8 nibble,u8 port,u8 rs_port,u8 rs_pin,u8 cmd,u8 en_port,u8 en_pin){
	if(mode==1){
		GPIO_WRITE_PORT(port,cmd);
		GPIO_WRITE_PIN(rs_port,rs_pin,0);
		ENABLE_SET(en_port,en_pin);
	}else{
		if(nibble==1){
			GPIO_HIGH_NIBBLE_WRITE(port,cmd>>4);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			GPIO_HIGH_NIBBLE_WRITE(port,cmd);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			_delay_ms(1);
		}else{
			GPIO_LOW_NIBBLE_WRITE(port,cmd>>4);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			GPIO_HIGH_NIBBLE_WRITE(port,cmd);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			_delay_ms(1);
		}
	}
}
void LCD_SEND_CHAR(u8 mode,u8 nibble,u8 port,u8 rs_port,u8 rs_pin,u8 en_port,u8 en_pin,u8 data){
	if(mode==1){
		GPIO_WRITE_PORT(port,data);
		GPIO_WRITE_PIN(rs_port,rs_pin,1);
		ENABLE_SET(en_port,en_pin);
		_delay_ms(1);
	}else{
		if(nibble==1){
			GPIO_HIGH_NIBBLE_WRITE(port,data>>4);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			GPIO_HIGH_NIBBLE_WRITE(port,data);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			_delay_ms(1);
		}else{
			GPIO_LOW_NIBBLE_WRITE(port,data>>4);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			GPIO_HIGH_NIBBLE_WRITE(port,data);
			GPIO_WRITE_PIN(rs_port,rs_pin,0);
			ENABLE_SET(en_port,en_pin);
			_delay_ms(1);
		}
	}
}