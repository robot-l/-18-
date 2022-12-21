#include "encoder.h"

int16 SpeedLF=0;
int16 SpeedRF=0;
int16 SpeedLB=0;
int16 SpeedRB=0;
int16 DeltaB;

/*====================encoder_get====================
描述：读取编码器数值
参数：无
返回：无
=====================================================*/
void encoder_get(void)
{
    SpeedRB = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0);	//编码器一,右后
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0);
	
    SpeedLF = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2);	//编码器二,左前
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2);  
	
		SpeedLB =qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );	//编码器三, 左后
		qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
	
	  SpeedRF = -qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);//编码器四,右前
    qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
}

/*====================encoder_entry====================
描述：编码器定时器入口函数
			打印编码器数值，打印超过四个数据会卡死
参数：无
返回：无
=======================================================*/

void encoder_entry()
{
		encoder_get();
		//lcd_showint16(0,6,SpeedLF+SpeedRF);
		//lcd_showint16(0,7,SpeedLB+SpeedRB);
	
		//lcd_showint16(60,6,SpeedRF);
		//lcd_showint16(60,7,SpeedRB);
		//DeltaB=SpeedLB+SpeedRB;
		//lcd_showstr(0,80,"deltaB:");
		//lcd_showint16(1,80,SpeedLB);
}

void encoder_calculate_entry()
{
		DeltaB=SpeedLB+SpeedRB;
		lcd_showstr(0,80,"deltaB:");
		lcd_showint16(1,80,SpeedLB);
}

void encoder_init()
{
		qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);//正交编码器1    左后 
	
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);//正交编码器2     右后
	
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);//正交编码器3    左前
	
    qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);//正交编码器4   右前 
	
		rt_timer_t ThEncoder,ThBack;
		ThEncoder = rt_timer_create("encoder",
																  encoder_entry,
																	RT_NULL,
																	50,RT_TIMER_FLAG_PERIODIC);
		if (RT_NULL != ThEncoder)
		{
				rt_timer_start(ThEncoder);
		}
}