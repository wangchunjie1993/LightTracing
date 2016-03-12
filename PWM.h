#include<avr/io.h>
#include"def.h"

#ifndef __PWM_H__
#define __PWM_H__

void PWM_init(int duty);
void PWM_modify(int duty);

#endif
