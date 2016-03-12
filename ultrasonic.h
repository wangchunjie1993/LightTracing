#include<avr/io.h>
#include"def.h"

#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

void ultrasonic_init();
int read_ultrasonic_distance();

#endif
