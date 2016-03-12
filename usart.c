#include<avr/io.h>
#include<avr/interrupt.h>
#include"def.h"

uchar data_rx=0;				//串口接收到的数据

char receive_count=1;
uchar dis_high=0,dis_low=0;

/***************
* usart0
***************/
void usart0_init(uint baud)
{
	UBRR0H=baud<<8;
	UBRR0L=baud;
	UCSR0B|=(1<<7)|(1<<4)|(1<<3);
	UCSR0C|=(3<<0);
}

void usart0_transmit(uchar data)
{
	while(!(UCSR0A&(1<<5)));
	UDR0=data;
}

void usart0_puts(uchar *str)
{
	while(*str)
	{
		usart0_transmit(*str++);
	}
}

SIGNAL(USART0_RX_vect)
{
	//uchar data_rx;
	data_rx=UDR0;
}



/***************
* usart1
***************/
void usart1_init(uint baud)
{
	UBRR1H=baud<<8;
	UBRR1L=baud;
	UCSR1B|=(1<<7)|(1<<4)|(1<<3);
	UCSR1C|=(3<<0);
}

void usart1_transmit(uchar data)
{
	while(!(UCSR1A&(1<<5)));
	UDR1=data;
}

void usart1_puts(uchar *str)
{
	while(*str)
	{
		usart1_transmit(*str++);
	}
}

SIGNAL(USART1_RX_vect)
{
	//uchar data_rx;
	data_rx=UDR1;
	if(receive_count==2)
	{
		dis_high=data_rx;
	}	
	else if(receive_count==1)
	{
		dis_low=data_rx;
	}
	receive_count--;
}
