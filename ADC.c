#include<avr/io.h>
#include<util/delay.h>
#include"def.h"

/***************************
* ADC的第num通道初始化,num--(0,7)
***************************/
void ADC_init(uchar num)
{
	DDRF&=~(1<<num);
	PORTF&=~(1<<num);
	ADMUX&=(~(1<<7));
	ADMUX|=(1<<6);
	ADMUX&=~(0x1f);
	ADMUX|=(1<<5)|num;
	ADCSRA|=(1<<1)|(1<<2)|(1<<7);
}

/***************************
* 读取ADC的值
***************************/
int read_ADC()
{	
	_delay_ms(100);
	int ad_val=0;
	ADCSRA|=(1<<6);
	while((ADCSRA&(1<<4))==0);

	ad_val|=(ADCL>>6);
	ad_val|=(ADCH<<2);
	return ad_val;
}
