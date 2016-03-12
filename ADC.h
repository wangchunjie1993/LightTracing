#include<avr/io.h>
#include"def.h"

#ifndef __ADC_H__
#define __ADC_H__

void ADC_init(uchar num);
int read_ADC();

#endif
