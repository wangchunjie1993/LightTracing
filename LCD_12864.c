//ICC-AVR application builder : 2013/7/4 18:16:05
// Target : M128
// Crystal: 8.0000Mhz

#include<avr/io.h>
#include"def.h"
#include"lib.h"


 //���� : ����Һ���Ĵ���ͨ��Э�飬��������
void write_bit(uchar bits)
{
 uchar i;
 for(i=0;i<8;i++)
 {
  if((bits<<i) & 0x80)
  {
   SID_UP;
  }
  else
  {
   SID_DOWN;
  }
  SCLK_DOWN;
  SCLK_UP;
 }
}


//���� : д����ָ��
void write_command(uchar command)
{
 CS;
 write_bit(0xf8);//���ڸ�ʽ��д����ָ��
 write_bit(command & 0xf0);//д��4λ
 write_bit((command<<4) & 0xf0);//д��4λ
 delay_ms(2);
}

//���� : д��������
void write_data(uchar data)
{
 CS;
 write_bit(0xfa);//д����
 write_bit(data & 0xf0);//д��4λ
 write_bit((data<<4) & 0xf0);//д��4λ
 delay_ms(2);
}

 //�趨��ʾλ��
void write_address(uchar x,uchar y)
{
 uchar add;
 switch(x)
 {
  case 0:add=0x80+y;break;
  case 1:add=0x90+y;break;
  case 2:add=0x88+y;break;
  case 3:add=0x98+y;break;
 }
 write_command(add);
 delay_us(90);
}

void write_word(uchar *pos)
{
  while(*pos)
  {
   write_data(*pos);
   pos++;
   delay_us(90);
  }
}
void init_12864(void)
{
 //RST_DOWN;
 //delay(10);
 //RST_UP;
 //delay(50);
 write_command(0x30);//��������:����Ϊ����ָ�
 delay_us(90);
 write_command(0x0c);//������ʾ������ʾ����λ��
 delay_us(90);
 write_command(0x01);//����
 delay_ms(8);
 PSB;
}



