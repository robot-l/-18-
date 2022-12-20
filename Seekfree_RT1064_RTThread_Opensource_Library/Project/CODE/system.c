/*=========================system_init============================
* ÃèÊö£ºÓ²¼þ³õÊ¼»¯
* 
*
================================================================*/

#include "system.h"

/*=======================system_entry=============================



==================================================================*/
void system_entry(void *parameter)
{
	lcd_init();
//	rt_device_t dev;
//	dev=rt_device_find("adc1");
	button_init();
	//camera();
	//encoder_init();
}


void system_init()
{
	rt_thread_t Th_display;
	Th_display = rt_thread_create("system",
																system_entry,
																RT_NULL,
																4096,20,5);
	
	if (RT_NULL!=Th_display)
	{
		rt_thread_startup(Th_display);
	}
}

