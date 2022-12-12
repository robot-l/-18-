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
static rt_uint8_t thread2_stack[1024];						// ��̬�߳�Ҫ�õ���ջ����
struct rt_thread thread2_thread;							// ��̬�߳̿��ƿ�
// **************************** �������� ****************************

// **************************** �������� ****************************
void thread1_entry (void *parameter);
void thread2_entry (void *parameter);
int dynamic_thread_example (void);
int static_thread_example (void);

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���dynamic_thread_example�������г�ʼ��
INIT_APP_EXPORT(dynamic_thread_example);					// Ӧ�ó�ʼ��

//ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���static_thread_example�������г�ʼ��
INIT_APP_EXPORT(static_thread_example);						// Ӧ�ó�ʼ��

// ��̬��������
// ������û�п���RT_USING_HEAP�궨������ֻ��ʹ�þ�̬�ķ��������̡߳��ź������������ȵ�
// ���ߵ�������Ҫָ�����ƿ���ƿ����ջ��λ�õ�ʱ��Ҳ�����þ�̬��������

// ��̬��������
// ��̬������ؿ���RT_USING_HEAP�궨��
// ��̬�����ô��������ǲ����Լ�������ƿ����ջ���飬������ʱ����д�Ĳ������ӵ��ٷǳ��ķ���
// ���HEAP��С�����ˣ�������board.c���ҵ�RT_HEAP_SIZE������޸�

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
// @brief		�߳�1���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread1_entry(void *parameter)
{
	while(1)
	{
		rt_kprintf("dynamic thread is running.\n");
		rt_thread_mdelay(1000);
	}
}

//------------------------------------------------------------
// @brief		�߳�2���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread2_entry(void *parameter)
{
	while(1)
	{
		rt_kprintf("static thread is running.\n");
		rt_thread_mdelay(500);
	}
}

//------------------------------------------------------------
// @brief		��̬�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int dynamic_thread_example(void)
{
	// �߳̿��ƿ�ָ��
	rt_thread_t tid1;
	// ������̬�߳�
	tid1 = rt_thread_create("thread1",						// �߳�����
		thread1_entry,										// �߳���ں���
		RT_NULL,											// �̲߳���
		1024,												// 1024 ���ֽڵ�ջ�ռ�
		5,													// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
															// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		5);													// ʱ��ƬΪ5

	rt_kprintf("create dynamic thread.\n");
	if(tid1 != RT_NULL)										// �̴߳����ɹ�
	{
		rt_kprintf("thread1 dynamic thread create OK.\n");
		rt_thread_startup(tid1);							// ���и��߳�
	}
	else													// �̴߳���ʧ��
	{
		rt_kprintf("thread1 dynamic thread create ERROR.\n");
		return 1;
	}

	return 0;
}

//------------------------------------------------------------
// @brief		��̬�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int static_thread_example(void)
{
	rt_err_t res;
	//������̬�߳�
	res = rt_thread_init(
		&thread2_thread,									// �߳̿��ƿ�
		"thread2",											// �߳�����
		thread2_entry,										// �߳���ں���
		RT_NULL,											// �̲߳���
		thread2_stack,										// ջ����ʼ��ַ
		sizeof(thread2_stack),								// ջ��С
		3,													// �߳����ȼ�Ϊ3����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
															// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		5													// ʱ��ƬΪ5
	);

	rt_kprintf("create static thread.\n");

	if(res == RT_EOK)										// �̴߳����ɹ�
	{
		rt_kprintf("thread2 static thread create OK\n");
		rt_thread_startup(&thread2_thread);					// ���и��߳�

	}
	else													// �̴߳���ʧ��
	{
		rt_kprintf("thread2 static thread create ERROR\n");
		return 1;
	}
	return 0;
}
// **************************** �������� ****************************
