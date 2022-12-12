#include "button.h"

#define KEY_1		C17				//定义按键

uint8 Key1Status = 1;
uint8 Key1Last=1;

uint8 count=0;
uint8 count2=0;

void button_entry(void*parameter)
{
		Key1Last=Key1Last;
		Key1Status = gpio_get(KEY_1);
		//lcd_showint8(0,5,key1_status);
		if (!Key1Status && Key1Status != Key1Last)
		{
				count++;
		}
		lcd_showint8(80,7,count);
		rt_kprintf("%d",count);
}

void time2_entry(void *parameter)
{
		count2++;
		lcd_showint8(80,6,count2);
}

void button_init(void)
{
		rt_timer_t button_timer,tim2;
		
		gpio_init(KEY_1, GPI, GPIO_HIGH, GPIO_PIN_CONFIG);			// 初始化为GPIO浮空输入 默认上拉高电平
		gpio_interrupt_init(KEY_1   ,FALLING,GPIO_INT_CONFIG);//下降沿触发中断
	
		button_timer = rt_timer_create("button", button_entry, 
																		RT_NULL, 
																		10, 
																		RT_TIMER_FLAG_PERIODIC);
	
		tim2 = rt_timer_create("tim2",time2_entry,RT_NULL,2,RT_TIMER_FLAG_PERIODIC);
	
    if(RT_NULL != button_timer) 
    {
        rt_timer_start(button_timer);
    }
		if(RT_NULL != tim2) 
    {
        rt_timer_start(tim2);
    }
		
}