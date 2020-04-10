#ifndef REGISTERS_H_
#define REGISTERS_H_
//---GPIO_REGISTERS---


//PORTA
#define XDDRA *((volatile unsigned char * const )0x3A)
#define XPORTA *((volatile unsigned char * const )0x3B)
#define XPINA *((volatile unsigned char * const )0x39)


//PORTB
#define XDDRB *((volatile unsigned char * const )0x37)
#define XPORTB *((volatile unsigned char * const )0x38)
#define XPINB *((volatile unsigned char * const )0x36)


//PORTC
#define XDDRC *((volatile unsigned char * const )0x34)
#define XPORTC *((volatile unsigned char * const )0x35)
#define XPINC *((volatile unsigned char * const )0x33)


//PORTD
#define XDDRD *((volatile unsigned char * const )0x31)
#define XPORTD *((volatile unsigned char * const )0x32)
#define XPIND *((volatile unsigned char * const )0x30)
//---------------------
#endif