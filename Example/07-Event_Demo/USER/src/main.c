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
#define EVENT_FLAG3		(1<<3)
#define EVENT_FLAG5		(1<<5)
// **************************** �궨�� ****************************

// **************************** �������� ****************************
rt_event_t event;
// **************************** �������� ****************************

// **************************** �������� ****************************
void thread1_entry (void *parameter);
void thread2_entry (void *parameter);
int event_example (void);

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���event_example�������г�ʼ��
INIT_APP_EXPORT(event_example);									// Ӧ�ó�ʼ��

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
// @brief		�߳����
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread1_entry (void *parameter)
{
	rt_uint32_t e;
	if(rt_event_recv
		(event,													// �¼����ƿ�
		(EVENT_FLAG3 | EVENT_FLAG5),							// �¼���־3���¼���־5
		(RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR),				// �¼��봥����������ɺ�����¼���־λ
		RT_WAITING_FOREVER,										// һֱ�ȴ�
		&e) == RT_EOK)
	{
		rt_kprintf("thread1: AND recv event 0x%x\n", e);
	}
}

//------------------------------------------------------------
// @brief		�߳����
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread2_entry (void *parameter)
{
	rt_kprintf("thread2: send event3\n");
	rt_event_send(event, EVENT_FLAG3);
	rt_thread_mdelay(200);

	rt_kprintf("thread2: send event5\n");
	rt_event_send(event, EVENT_FLAG5);
	rt_thread_mdelay(200);

	rt_kprintf("thread2 leave .\n");
}

//------------------------------------------------------------
// @brief		�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int event_example (void)
{
	rt_thread_t tid;

	event = rt_event_create("event", RT_IPC_FLAG_FIFO);

	// ������̬�߳�
	tid = rt_thread_create("thread1",							// �߳�����
		thread1_entry,											// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// 1024 ���ֽڵ�ջ�ռ�
		5,														// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
																// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		5);														// ʱ��ƬΪ5

	if(tid != RT_NULL)											// �̴߳����ɹ�
	{
		rt_kprintf("create thread1 OK\n");
		//���и��߳�
		rt_thread_startup(tid);
	}

	//������̬�߳�
	tid = rt_thread_create("thread2",							// �߳�����
		thread2_entry,											// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// 1024 ���ֽڵ�ջ�ռ�
		5,														// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
																// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		5);														// ʱ��ƬΪ5

	if(tid != RT_NULL)											// �̴߳����ɹ�
	{
		rt_kprintf("create thread2 OK\n");
		//���и��߳�
		rt_thread_startup(tid);
	}

	return 1;
}
// **************************** �������� ****************************
