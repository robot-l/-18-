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
void thread1_entry (void *parameter);
void thread2_entry (void *parameter);
int critical_section_example(void);

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���critical_section_example�������г�ʼ��
INIT_APP_EXPORT(critical_section_example);					// Ӧ�ó�ʼ��

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
void thread1_entry (void *parameter)
{
	while(1)
	{
		// �����������������󽫲����л��������̣߳�����Ӧ�ж� 
		rt_enter_critical();
		// ���½����ٽ��� 

		count += 10;										// ����ֵ+10

		// ���������� 
		rt_exit_critical();

		rt_kprintf("thread = %d , count = %d\n", 10, count);
		rt_thread_mdelay(1000);
	}
}

//------------------------------------------------------------
// @brief		�߳�2��ں���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread2_entry (void *parameter)
{
	while(1)
	{
		// �����������������󽫲����л��������̣߳�����Ӧ�ж�
		rt_enter_critical();
		// ���½����ٽ���

		count += 20;										// ����ֵ+20

		// ����������
		rt_exit_critical();

		rt_kprintf("thread = %d , count = %d\n", 20, count);
		rt_thread_mdelay(2000);
	}
}

//------------------------------------------------------------
// @brief		�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int critical_section_example (void)
{
	// �߳̿��ƿ�ָ��
	rt_thread_t tid;
	// ������̬�߳�
	tid = rt_thread_create("thread_10",						// �߳�����
		thread1_entry,										// �߳���ں���
		RT_NULL,											// �̲߳���
		1024,												// ջ�ռ�
		5,													// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
															// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		10);												// ʱ��Ƭ

	if(tid != RT_NULL)										// �̴߳����ɹ�
	{
		// ���и��߳�
		rt_thread_startup(tid);
	}

	tid = rt_thread_create("thread_20",						// �߳�����
		thread2_entry,										// �߳���ں���
		RT_NULL,											// �̲߳���
		1024,												// ջ�ռ�
		3,													// �߳����ȼ�Ϊ3����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
															// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		10);												// ʱ��Ƭ

	if(tid != RT_NULL)										// �̴߳����ɹ�
	{
		rt_thread_startup(tid);								// ���и��߳�
	}

	return 0;
}
// **************************** �������� ****************************
