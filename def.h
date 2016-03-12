#ifndef __DEF_H__
#define __DEF_H__

#define uchar unsigned char
#define uint unsigned int

/***********木板参数(cm)**************/
#define a 110	//宽
#define b 115	//高
#define L1 116
#define L2 149
#define R 25
#define START_POINT 6
#define OFFSET 9
#define PER_STEP_1 207.5
#define PER_STEP_2 203.5

/***************按键定义*****************/
#define MOD (PIND&0x01)
#define SHU (PIND&0x02)
#define OK  (PIND&0x04)


/************1602LCD控制引脚************/
/*#define RS_1 PORTA|=BIT(5)
#define RS_0 PORTA&=~BIT(5)

#define RW_1 PORTA|=BIT(6)
#define RW_0 PORTA&=~BIT(6)

#define E_1 PORTA|=BIT(7)
#define E_0 PORTA&=~BIT(7)*/

//#define EN_0 PORTF&=~BIT(3);
//#define EN_1 PORTF|=BIT(3);
//#define RS_C PORTF&=~BIT(2);
//#define RS_D PORTF|=BIT(2);


/******************12864LCD控制引脚********************/
#define CS PORTG |= (1<<2)			//片选信号
#define SID_UP PORTG|= (1<<3)		//高电平数据信号
#define SID_DOWN PORTG&= ~(1<<3)	//低电平数据信号
#define SCLK_UP PORTG|=(1<<4)		//同步时钟高电平信号
#define SCLK_DOWN PORTG &= ~(1<<4)	//同步时钟低电平信号
#define RST_UP PORTA|=(1<<5)		//复位信号无效
#define RST_DOWN PORTA &= ~(1<<5)	//复位信号有效
#define PSB PORTG&=~(1<<1)			//并行、串行选择端


/**************光电开关****************/
#define FRONT	(PINA&(1<<0))
#define LEFT	(PINA&(1<<1))
#define RIGHT	(PINA&(1<<2))

/************超声波控制引脚*************/
/*#define Trig_1 PORTB|=BIT(2)
#define Trig_0 PORTB&=~BIT(2)
#define Echo (PINB&BIT(3))*/


/************自由摆参数**************/
#define g 			9.8				//重力加速度
#define THRESHOLD	0.07			//用于检测自由摆放下时加速度变化量的阈值
#define ERROR		-2				//初始位置自由摆相对竖直位置倾角	

typedef union
{
	uchar data_trans[4];		//串口用于字节传输
	float data_use;				//直接使用的数据
}float_data;


/******************舵机与电机转动单位角*******************/
#define STEERING_STEP	40
#define MOTOR_STEP		116


#endif
