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
// ����һ���ַ���
static char mb_str1[] = "i am a mail!";

// ������ƿ�ָ��
static rt_mailbox_t mb;
// **************************** �������� ****************************

// **************************** �������� ****************************
void thread1_entry (void *parameter);
void thread2_entry (void *parameter);
int mailbox_example (void);

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���mailbox_example�������г�ʼ��
INIT_APP_EXPORT(mailbox_example);								// Ӧ�ó�ʼ��

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
	char *str;

	rt_kprintf("thread1:try to recv a mail.\n");

	if(rt_mb_recv(mb,											// ������ƿ�
		(rt_ubase_t *)&str,										// ����������ַ��� ���� 32bit ��С���ʼ�
		RT_WAITING_FOREVER)										// һֱ�ȴ�
		== RT_EOK)
	{
		rt_kprintf("thread1:get a mail from mailbox.\nthe content :%s\n", str);	// ���������Ϣ
	}
	rt_mb_delete(mb);											// ɾ������
}

//------------------------------------------------------------
// @brief		�߳����
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread2_entry (void *parameter)
{
	rt_kprintf("thread2:try to send a mail.\n");
	// ������ʹ�õķ�ʽ�ǽ��ַ����ĵ�ַȡֵ �õ� 32bit �ĵ�ֵַ����
	rt_mb_send(mb, (rt_uint32_t)&mb_str1);						// �����ʼ�
}

//------------------------------------------------------------
// @brief		���䴴���Լ�����
// @param		void
// @return		void
// Sample usage:
//------------------------------------------------------------
int mailbox_example (void)
{
	rt_thread_t t1,t2;

	// ��������
	mb = rt_mb_create("mb",
		4,														// ���� ������Ϊ 4 ���ʼ�
		RT_IPC_FLAG_FIFO										// �Ƚ��ȳ�
		);

	t1 = rt_thread_create(
		"thread1",												// �߳�����
		thread1_entry,											// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// ջ�ռ��С
		4,														// �����߳����ȼ�
		5);														// ʱ��Ƭ

	if(t1 != RT_NULL)											// �̴߳����ɹ�
	{
		rt_thread_startup(t1);									// ���и��߳�
	}

	t2 = rt_thread_create(
		"thread2",												// �߳�����
		thread2_entry,											// �߳���ں���
		RT_NULL,												// �̲߳���
		1024,													// ջ�ռ��С
		3,														// �����߳����ȼ�
		5);														// ʱ��Ƭ

	if(t2 != RT_NULL)											// �̴߳����ɹ�
	{
		rt_thread_startup(t2);									// ���и��߳�
	}

	return 0;
}
// **************************** �������� ****************************
