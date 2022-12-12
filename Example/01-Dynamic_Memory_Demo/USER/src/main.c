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

int dynmem_example(void);
void thread1_entry(void *parameter);

// ʹ��INIT_APP_EXPORT���Զ���ʼ����Ҳ����ͨ���������߳��ڵ���dynmem_example�������г�ʼ��
INIT_APP_EXPORT(dynmem_example);					// Ӧ�ó�ʼ��

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
// @brief		�̴߳����Լ�����
// @param		void		��
// @return		void
// Sample usage:
//------------------------------------------------------------
int dynmem_example(void)
{
	// �߳̿��ƿ�ָ��
	rt_thread_t tid;
	lcd_init();
	// ������̬�߳�
	tid = rt_thread_create("thread1",				// �߳�����
		thread1_entry,								// �߳���ں���
		RT_NULL,									// �̲߳���
		1024,										// 1024 ���ֽڵ�ջ�ռ�
		5,											// �߳����ȼ�Ϊ5����ֵԽС�����ȼ�Խ�ߣ�0Ϊ������ȼ���
													// ����ͨ���޸�rt_config.h�е�RT_THREAD_PRIORITY_MAX�궨��(Ĭ��ֵΪ8)���޸����֧�ֵ����ȼ�
		5);											// ʱ��ƬΪ5


	if(tid != RT_NULL)								// �̴߳�����Ϊ��
	{
		rt_kprintf("create thread OK\n");
		lcd_showstr(0,0,"success");
		rt_thread_startup(tid);						// ���и��߳�
	}
	else											// �̴߳���ʧ��
	{
		rt_kprintf("create thread failed\n");
		lcd_showstr(0,0,"failed");
		return 0;
	}

	return 1;
}

//------------------------------------------------------------
// @brief		�߳���ں���
// @param		parameter	����
// @return		void
// Sample usage:
//------------------------------------------------------------
void thread1_entry(void *parameter)
{
	rt_uint32_t i = 0;
	rt_uint8_t *p = RT_NULL;						// �ڴ���ָ��
	while(1)
	{
		p = rt_malloc(1<<i++);						// �ڶ��������ڴ�
		if(p != RT_NULL)
		{
			rt_kprintf("get  memory : %dByte\n", 1<<i);
			lcd_showstr(0,1,"get:");
			lcd_showint32(30,1,1<<i,8);
			rt_free(p);								// �ͷ��ڴ�
			rt_kprintf("free  memory : %dByte\n", 1<<i);
			lcd_showstr(0,2,"free:");
			lcd_showint32(30,2,1<<i,8);
			p = RT_NULL;							// ָ�����
		}
		else
		{
			// HEAP��С�Ѿ��޷���������Ĵ�С��
			// ������board.c�� �޸�RT_HEAP_SIZE�궨�������Ĵ�С
			rt_kprintf("get memory : %dByte failed!!!\n",1<<i);
			lcd_showstr(0,0,"Byte failed");
			return;
		}
		rt_thread_mdelay(500);
	}
}
  



