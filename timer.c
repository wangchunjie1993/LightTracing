#include<avr/io.h>
#include"def.h"

/************************
* ��ʱ��3��ʼ����ÿ1s���һ�Σ�
************************/
void timer3_init()
{
	TCNT3=3035;
	TCCR3A=0x00;
	TCCR3B&=~(0x1f);
	ETIMSK|=(1<<2);

	TCCR3B|=(1<<2);
}

void timer3_start()
{
	TCCR3B|=(1<<2);
}

void timer3_stop()
{
	TCCR3B&=(~(1<<0))&(~(1<<1))&(~(1<<2));
}
