#include<avr/io.h>

#ifndef __MOTOR_H__
#define __MOTOR_H__

void motor_fast_init();
void motor_init();
void forward();
void forward_count(int count);
void left();
void left_count(int count);
void right();
void right_count(int count);
void motor_stop();

#endif
