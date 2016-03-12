#include<avr/io.h>
#include"def.h"

void PWM_init(int duty)		//��λ����PWM,����20ms,duty��Χ(0,20000),1ms�ߵ�ƽ��Ӧ1000,2ms�ߵ�ƽ��Ӧ2000   ���(700,2200) 0.4ms--2.2ms
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
