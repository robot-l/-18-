/*=========================system_init============================
* ������Ӳ����ʼ��
* 
*
================================================================*/

#include "system.h"
#include "UIdisplay.h"

void system_init()
{
	lcd_init();
	//button_init();
	//camera();
	encoder_init();
	display_init();
}

