#include<avr/io.h>
#include"def.h"

#ifndef __LIB_H__
#define __LIB_H__

void delay1ms(void);
void delayms(uint x);
void delay(uint x);
void delay_10us(void);
void delay_us(uchar us);
void delay_ms(uint ms);

#endif
