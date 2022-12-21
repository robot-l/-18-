#include "encoder.h"

int16 SpeedLF=0;
int16 SpeedRF=0;
int16 SpeedLB=0;
int16 SpeedRB=0;
int16 DeltaB;

/*====================encoder_get====================
��������ȡ��������ֵ
��������
���أ���
=====================================================*/
void encoder_get(void)
{
    SpeedRB = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0);	//������һ,�Һ�
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0);
	
    SpeedLF = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2);	//��������,��ǰ
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2);  
	
		SpeedLB =qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );	//��������, ���
		qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
	
	  SpeedRF = -qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);//��������,��ǰ
    qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
}

/*====================encoder_entry====================
��������������ʱ����ں���
			��ӡ��������ֵ����ӡ�����ĸ����ݻῨ��
��������
���أ���
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
		qtimer_quad_init(QTIMER_2,QTIMER2_TIMER0_C3,QTIMER2_TIMER3_C25);//����������1    ��� 
	
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);//����������2     �Һ�
	
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);//����������3    ��ǰ
	
    qtimer_quad_init(QTIMER_3,QTIMER3_TIMER2_B18,QTIMER3_TIMER3_B19);//����������4   ��ǰ 
	
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