/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�


//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������

//���ش���ǰ������Լ�ʹ�õ��������ڹ���������������Ϊ�Լ���ʹ�õ�

#include "headfile.h"

#include "display.h"
#include "timer_pit.h"
#include "encoder.h"
#include "buzzer.h"
#include "button.h"
#include "motor.h"
#include "elec.h"
#include "openart_mini.h"
#include "smotor.h"

rt_sem_t camera_sem;

int main(void)
{
	camera_sem = rt_sem_create("camera", 0, RT_IPC_FLAG_FIFO);

    mt9v03x_csi_init();
    icm20602_init_spi();
    
    display_init();
    encoder_init();
    buzzer_init();
    button_init();
    motor_init();
    elec_init();
    openart_mini();
    smotor_init();
    timer_pit_init();
    
    EnableGlobalIRQ(0);
    while (1)
    {
		//�ȴ�����ͷ�ɼ����
        rt_sem_take(camera_sem, RT_WAITING_FOREVER);
        //rt_thread_mdelay(10);
        //��ʼ��������ͷͼ��
        
        
        //����ͼ��������ģ������֮���λ��ƫ��
        
        
        
        //����ƫ�����PD����
        
        
        //PD����֮���ֵ����Ѱ������Ŀ���
        smotor1_control(50);
    }
}

  



