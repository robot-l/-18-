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

// **************************** �궨�� ****************************
// **************************** �궨�� ****************************

// **************************** �������� ****************************
static rt_uint32_t count = 0;
// **************************** �������� ****************************

// **************************** �������� ****************************
void thread_slice_10_entry (void *parameter);
void thread_slice_20_entry (void *parameter);
int time_slice_20_thread_example (void);
int time_slice_10_thread_example (void);

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���time_slice_10_thread_example�������г�ʼ��
INIT_APP_EXPORT(time_slice_10_thread_example);					// Ӧ�ó�ʼ��

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���time_slice_20_thread_example�������г�ʼ��
INIT_APP_EXPORT(time_slice_20_thread_example);					// Ӧ�ó�ʼ��

int main(void)
{
	//�˴���д�û�����(���磺�����ʼ�������)

    gpio_init(B9, GPO, 0, GPIO_PIN_CONFIG);


    EnableGlobalIRQ(0);
    while (1)
    {
        //�˴���д��Ҫѭ��ִ�еĴ���
        
        gpio_toggle(B9);
        rt_thread_mdelay(100);
    }
}

//------------------------------------------------------------
// @brief		�߳�1��ں���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread_slice_10_entry(void *parameter)
{
	rt_thread_mdelay(10);										// ��ʱ�ȴ�finsh��ʼ�����

	while(1)
	{
		if(0 == (count % 5))
		{
			rt_enter_critical();
			// �����ٽ��� �����ӡ��ʱ�������̴߳��
			rt_kprintf("time slice 10 is running, count = %d\n", count);
			rt_exit_critical();
			if(200 <= count)
			{
				return;
			}
		}
		count++;
	}
}

//------------------------------------------------------------
// @brief		�߳�2��ں���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread_slice_20_entry(void *parameter)
{
	rt_thread_mdelay(10);										// ��ʱ�ȴ�finsh��ʼ�����

	while(1)
	{
		if(0 == (count % 5))
		{
			rt_enter_critical();
			// �����ٽ��� �����ӡ��ʱ�������̴߳��
			rt_kprintf("time slice 20 is running, count = %d\n", count);
			rt_exit_critical();
			if(200 <= count)
			{
				return;
			}
		}
		count++;
	}
}

//------------------------------------------------------------
// @brief		��̬�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int time_slice_10_thread_example(void)
{
	// �߳̿��ƿ�ָ��
	rt_thread_t tid1;

	// ������̬�߳�
	tid1 = rt_thread_create("thread_10",						// �߳�����
		thread_slice_10_entry,									// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// 1024 ���ֽڵ�ջ�ռ�
		5,														// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
																// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		20);													// ʱ��ƬΪ20

	rt_kprintf("create time slice 10 thread...\n\n");
	if(tid1 != RT_NULL)											// �̴߳����ɹ�
	{
		rt_kprintf("time slice 10 thread create OK...\n\n");
		rt_thread_startup(tid1);								// ���и��߳�
	}
	else														// �̴߳���ʧ��
	{
		rt_kprintf("time slice 10 thread create ERROR...\n\n");
		return 1;
	}

	return 0;
}

//------------------------------------------------------------
// @brief		�̴߳����Լ�����
// @param		void
// @return		void
// Sample usage:
//------------------------------------------------------------
int time_slice_20_thread_example(void)
{
	// �߳̿��ƿ�ָ��
	rt_thread_t tid1;
	// ������̬�߳�
	tid1 = rt_thread_create("thread_20",						// �߳�����
		thread_slice_20_entry,									// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// 1024 ���ֽڵ�ջ�ռ�
		5,														// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
																// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		10);													// ʱ��Ƭ

	rt_kprintf("create time slice 20 thread...\n\n");
	if(tid1 != RT_NULL)											// �̴߳����ɹ�
	{
		rt_kprintf("time slice 20 thread create OK...\n\n");
		rt_thread_startup(tid1);								// ���и��߳�
	}
	else														// �̴߳���ʧ��
	{
		rt_kprintf("time slice 20 thread create ERROR...\n\n");
		return 1;
	}

	return 0;
}
// **************************** �������� ****************************
