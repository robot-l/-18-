#include "headfile.h"
#include "encoder.h"
#include "display.h"





void display_entry(void *parameter)
{
	ips114_clear(BLACK);
    while(1)
    {
        ips114_displayimage032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W/2, MT9V03X_CSI_H/2);//��С��ʾ�������ͬ����ʾһЩ����
        ips114_showint16(0, 4, icm_gyro_x);
        ips114_showint16(0, 5, icm_acc_x);
        ips114_showint16(0, 6, speed_l);
        ips114_showint16(0, 7, speed_r);
    }
    
}






void display_init(void)
{
    rt_thread_t tid;
    
    //��ʼ����Ļ
    ips114_init();
    
    //������ʾ�߳� ���ȼ�����Ϊ31
    tid = rt_thread_create("display", display_entry, RT_NULL, 1024, 31, 30);
    
    //������ʾ�߳�
    if(RT_NULL != tid)
    {
        rt_thread_startup(tid);
    }
}