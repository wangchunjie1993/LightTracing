#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"def.h"
#include"lib.h"
#include"ADC.h"
#include"PWM.h"
#include"motor.h"
#include"ultrasonic.h"
#include"LCD_12864.h"
#include"timer.h"
#include"usart.h"

int light_intensity_curr=0,light_intensity_prev=0;			//当前光强值与前一次光强值
int PWM_duty=1450;			//舵机PWM占空比
int read_distance_flag=0;			//读取超声波距离标志
int refresh_charge_state_flag=0;			//刷新显示充电状态
int battery_voltage=0;			//电池电压
//int charge_voltage=0;			//充电电压
//int charge_current=0;			//充电电流
int distance=300;			//超声波测出的距离
extern int ctc_count;
extern uchar stop_flag;

void port_init();			
void car_find_direction();
void plate_find_direction();
void left_45_adjust();
void right_45_adjust();
void forward_adjust();
void recover();
void measure_charge_state();
void display_init_charge_state();
void refresh_charge_state();

int main()
{
	port_init();
	PWM_init(1450);
	motor_fast_init();
	ultrasonic_init();
	init_12864();
	timer3_init();

	SREG=0x80;
	_delay_ms(300);

	display_init_charge_state();
	
	//_delay_ms(2000);

	//car_find_direction();
	plate_find_direction();
	recover();
	
	timer3_start();
	
	while(distance>=200)
	{
		if(FRONT==0)
		{
			timer3_stop();
			motor_init();
			left_45_adjust();
			left_45_adjust();
			forward_adjust(3000);
			recover();
			motor_fast_init();

			timer3_start();
		}
		else if(LEFT==0)
		{
			timer3_stop();
			motor_init();
			right_45_adjust();
			forward_adjust(3000);
			recover();
			motor_fast_init();

			timer3_start();
		}
		else if(RIGHT==0)
		{
			timer3_stop();
			motor_init();
			left_45_adjust();
			forward_adjust(3000);
			recover();
			motor_fast_init();

			timer3_start();
		}
		else
		{
			//forward_adjust(700);
			//car_find_direction();
			if((PWM_duty-1450>200)||(1450-PWM_duty>200))
			{
				motor_stop();
				
				
				plate_find_direction();
				recover();
				motor_init();
				
				car_find_direction();
				motor_fast_init();
			}

			forward();
			plate_find_direction();
		}


		if(read_distance_flag==1)
		{
			read_distance_flag=0;
			distance=read_ultrasonic_distance();
		}
		if(refresh_charge_state_flag>=5)
		{
			refresh_charge_state_flag=0;
			refresh_charge_state();
		}
	}

	motor_stop();
	while(1);
}


/*int main()
{
	port_init();
	PWM_init(1450);
	ADC_init(0);
	usart0_init(103);
	motor_init();
	_delay_ms(1000);
	SREG=0x80;
	while(1)
	{	
		//left_count(2180);
		plate_find_direction();
		//_delay_ms(1000);
		battery_voltage=read_ADC();
		battery_voltage/=2.048;
		usart0_transmit(battery_voltage/100+48);
		usart0_transmit('.');
		usart0_transmit(battery_voltage%100/10+48);
		usart0_transmit(battery_voltage%10+48);
		usart0_transmit('V');
		_delay_ms(1000);
	}


	while(1);
}*/

void port_init()
{
	DDRB|=(1<<0)|(1<<1);		//控制步进电机方向

	DDRA&=(~(1<<0))&(~(1<<1))&(~(1<<2));		//光电对管引脚
	PORTA&=(~(1<<0))&(~(1<<1))&(~(1<<2));

	DDRG|=(1<<1)|(1<<2)|(1<<3)|(1<<4);		//液晶端口初始化
}

void car_find_direction()
{
	light_intensity_prev=read_ADC();
	left_count(MOTOR_STEP);
	light_intensity_curr=read_ADC();

	if(light_intensity_prev<light_intensity_curr)
	{
		do
		{
			light_intensity_prev=light_intensity_curr;
			left_count(MOTOR_STEP);
			light_intensity_curr=read_ADC();
		}while(light_intensity_prev<light_intensity_curr);
	}
	else
	{
		right_count(MOTOR_STEP);

		light_intensity_prev=read_ADC();
		right_count(MOTOR_STEP);
		light_intensity_curr=read_ADC();
		while(light_intensity_prev<light_intensity_curr)
		{
			light_intensity_prev=light_intensity_curr;
			right_count(MOTOR_STEP);
			light_intensity_curr=read_ADC();
		}
	}
}

void plate_find_direction()
{
	light_intensity_prev=read_ADC();
	PWM_duty+=STEERING_STEP;
	if(PWM_duty>=2200)
	{
		PWM_duty=2200;
	}
	PWM_modify(PWM_duty);
	light_intensity_curr=read_ADC();

	if(light_intensity_prev<light_intensity_curr)
	{
		do
		{
			light_intensity_prev=light_intensity_curr;
			PWM_duty+=STEERING_STEP;
			if(PWM_duty>=2200)
			{
				PWM_duty=2200;
			}
			PWM_modify(PWM_duty);
			light_intensity_curr=read_ADC();
		}while(light_intensity_prev<light_intensity_curr);
	}
	else
	{
		PWM_duty-=STEERING_STEP;
		if(PWM_duty<=700)
		{
			PWM_duty=700;
		}
		PWM_modify(PWM_duty);

		light_intensity_prev=read_ADC();
		PWM_duty-=STEERING_STEP;
		if(PWM_duty<=700)
		{
			PWM_duty=700;
		}
		PWM_modify(PWM_duty);
		light_intensity_curr=read_ADC();

		while(light_intensity_prev<light_intensity_curr)
		{
			light_intensity_prev=light_intensity_curr;
			PWM_duty-=STEERING_STEP;
			if(PWM_duty<=700)
			{
				PWM_duty=700;
			}
			PWM_modify(PWM_duty);
			light_intensity_curr=read_ADC();
		}
	}
}

void left_45_adjust()
{
	/*int i,n;
	n=1090/MOTOR_STEP;
	for(i=0;i<n;i++)
	{
		left_count(MOTOR_STEP);
		while(stop_flag==0)
		{
			plate_find_direction();
        }
	}*/
	left_count(1090);
	while(stop_flag==0)
	{
		plate_find_direction();
    }
}

void right_45_adjust()
{
	/*int i,n;
	n=1090/MOTOR_STEP;
	for(i=0;i<n;i++)
	{
		right_count(MOTOR_STEP);
		while(stop_flag==0)
		{
			plate_find_direction();
        }
	}*/
	right_count(1090);
	while(stop_flag==0)
	{
		plate_find_direction();
    }
}

void forward_adjust(int count)
{
	/*int i,n;
	n=count/500;
	for(i=0;i<n;i++)
	{
		forward_count(500);
		while(stop_flag==0)
		{
			plate_find_direction();
        }
	}*/
	forward_count(count);
	while(stop_flag==0)
	{
		plate_find_direction();
    }
}

void recover()
{
	int i,n;
	if((n=(PWM_duty-1450)/STEERING_STEP)>0)
	{
		for(i=0;i<n;i++)
		{
			left_count(MOTOR_STEP);
			while(stop_flag==0);
			PWM_duty-=STEERING_STEP;
			PWM_modify(PWM_duty);
		}
	}
	else
	{
		for(i=0;i<-n;i++)
		{
			right_count(MOTOR_STEP);
			while(stop_flag==0);
			PWM_duty+=STEERING_STEP;
			PWM_modify(PWM_duty);
		}
	}
	PWM_modify(1450);
	//car_find_direction();
}

void measure_charge_state()
{
	ADC_init(1);				//测量电池电压通道
	battery_voltage=read_ADC();
	//ADC_init(2);				//测量充电电压通道
	//charge_voltage=read_ADC();
	//ADC_init(3);				//测量充电电流通道
	//charge_current=read_ADC();

	ADC_init(0);				//恢复测量太阳能电池板电压通道
}

void display_init_charge_state()
{
	measure_charge_state();

	write_address(0,0);
	write_word("当前充电状态：");

	write_address(1,0);
	write_word("电池电压：");
	battery_voltage/=2.048;
	write_data(battery_voltage/100+48);
	write_data('.');
	write_data(battery_voltage%100/10+48);
	write_data(battery_voltage%10+48);
	write_data('V');

	/*write_address(2,0);
	write_word("充电电压：");
	charge_voltage/=2.048;
	write_data(charge_voltage/100+48);
	write_data('.');
	write_data(charge_voltage%100/10+48);
	write_data(charge_voltage%10+48);
	write_data('V');*/


	/*write_address(3,0);
	write_word("充电电流：");
	charge_voltage/=2.048;	
	write_data(charge_current/100+48);
	write_data('.');
	write_data(charge_current%100/10+48);
	write_data(charge_current%10+48);
	write_word("mA");*/
}

void refresh_charge_state()
{
	measure_charge_state();
	
	write_address(1,5);
	battery_voltage/=2.048;
	write_data(battery_voltage/100+48);
	write_data('.');
	write_data(battery_voltage%100/10+48);
	write_data(battery_voltage%10+48);
	write_data('V');

	/*write_address(2,5);
	charge_voltage/=2.048;
	write_data(charge_voltage/100+48);
	write_data('.');
	write_data(charge_voltage%100/10+48);
	write_data(charge_voltage%10+48);
	write_data('V');*/

	/*write_address(3,5);
	charge_voltage/=2.048;	
	write_data(charge_current/100+48);
	write_data('.');
	write_data(charge_current%100/10+48);
	write_data(charge_current%10+48);
	write_word("mA");*/
}

SIGNAL(TIMER3_OVF_vect)
{
	TCNT3=3035;
	read_distance_flag=1;

	refresh_charge_state_flag++;
}


SIGNAL(TIMER0_COMP_vect)
{
	ctc_count--;
	if(ctc_count<=0)
	{
		DDRB&=~(1<<4);
 		TIMSK&=~(1<<1);
		stop_flag=1;
	}
}

