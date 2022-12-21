/*=========================system_init============================
* ÃèÊö£ºÓ²¼þ³õÊ¼»¯
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

