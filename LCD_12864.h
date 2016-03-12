#include<avr/io.h>
#include"def.h"

#ifndef __LCD_12864_H__
#define __LCD_12864_H__

void write_command(uchar command);
void write_data(uchar data);
void write_address(uchar x,uchar y);
void write_word(uchar *pos);
void init_12864(void);

#endif
