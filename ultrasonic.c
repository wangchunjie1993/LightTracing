#include<avr/io.h>
#include"def.h"
#include"usart.h"

extern char receive_count;
extern uchar dis_high,dis_low;

void ultrasonic_init()
{
	usart1_init(103);
}

int read_ultrasonic_distance()
{
	receive_count=2;
	dis_high=dis_low=0;
	usart1_transmit(0x55);
	while(receive_count>=1);
	return (dis_high*256+dis_low);
}
