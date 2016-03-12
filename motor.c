#include<avr/io.h>
#include"def.h"
#include"lib.h"

int ctc_count=0;
uchar stop_flag=0;

void motor_init()
{
 TCCR0=0x00;
 TCNT0=0x00;
 OCR0=0xcc;
 TCCR0|=(7<<2);
}

void motor_fast_init()
{
 TCCR0=0x00;
 TCNT0=0x00;
 OCR0=0xa0;
 TCCR0|=(7<<2);
}

void forward()
{
	PORTB&=~(3<<0);
 	PORTB|=(1<<0);
	DDRB|=(1<<4);
}

void forward_count(int count)
{
 stop_flag=0;
 ctc_count=count;
 PORTB&=~(3<<0);
 PORTB|=(1<<0);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 //while(ctc_count>=0);
 //DDRB&=~(1<<4);
 //TIMSK&=~(1<<1);
}

void left()
{
	PORTB|=(3<<0);
	DDRB|=(1<<4);
}

void left_count(int count)
{
 stop_flag=0;
 ctc_count=count;
 PORTB|=(3<<0);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 //while(ctc_count>=0);
 //DDRB&=~(1<<4);
 //TIMSK&=~(1<<1);
}

void right()
{
	PORTB&=~(3<<0);
	DDRB|=(1<<4);
}

void right_count(int count)
{
 stop_flag=0;
 ctc_count=count;
 PORTB&=~(3<<0);
 TIMSK|=(1<<1);
 DDRB|=(1<<4);
 //while(ctc_count>=0);
 //DDRB&=~(1<<4);
 //TIMSK&=~(1<<1);
}

void motor_stop()
{
	DDRB&=~(1<<4);
}
