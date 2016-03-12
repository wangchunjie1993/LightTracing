#include<avr/io.h>
#include"def.h"

void PWM_init(int duty)		//相位修正PWM,周期20ms,duty范围(0,20000),1ms高电平对应1000,2ms高电平对应2000   舵机(700,2200) 0.4ms--2.2ms
{
	TCCR1A&=(~(3<<6))&(~(3<<0));
	TCCR1A|=(1<<7);
	
	TCCR1B&=(~(3<<3));
	TCCR1B|=(1<<4);
	TCCR1B&=(~(7<<0));
	TCCR1B|=(1<<1);		
	
	TCNT1=0;
	
	OCR1A=duty;	
	
	ICR1=20000;
	
	DDRB|=(1<<5);
}

void PWM_modify(int duty)
{
	OCR1A=duty;
}
