#include "camera.h"

void camera_entry(void *parameter)
{
		if (mt9v03x_csi_finish_flag)
		{
				mt9v03x_csi_finish_flag=0;
				lcd_displayimage032_zoom(mt9v03x_csi_image[0], 
																 MT9V03X_CSI_W, 
																 MT9V03X_CSI_H, 
																 80, 60);
		}
}

void camera()
{
		mt9v03x_csi_init();
		rt_timer_t ThCamera;
		ThCamera = rt_timer_create("camera",
																 camera_entry,
																 RT_NULL,
																 1,RT_TIMER_FLAG_PERIODIC);
		if (RT_NULL != ThCamera)
		{
				rt_timer_start(ThCamera);
		}
}