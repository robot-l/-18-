#include "UIdisplay.h"


//�����α�
ViewCursor cursor;
//����home�����������

ViewRow home[]={
		{MENU_NEXT,1,NULL,"Page1",0},
		{MENU_STAY,NULL,NULL,"Value1",10},
		{MENU_STAY,NULL,NULL,"Value2",10},
		{MENU_STAY,NULL,NULL,"Value3",10},
		{MENU_STAY,NULL,NULL,"Value4",10},
		{MENU_STAY,NULL,NULL,"Value5",10},
		{MENU_STAY,NULL,NULL,"Value6",10}
};



ViewRow page1[]={
		{MENU_NEXT,0,NULL,"back",0},
		{MENU_STAY,NULL,NULL,"Value7",0},
		{MENU_STAY,NULL,NULL,"Value8",0},
		{MENU_FUN,NULL,camera,"camera",0}
};


//���涨�壬ÿ����һ������ͬʱ��������֣����������ת
#define HOME       0
#define PAGE1      1
ViewMenu menu[]={
		DEFINE_MENU(home),
		DEFINE_MENU(page1)
};


void page_init(uint8 page)
{
		for(int i=0;i<menu[page].menu_len;i++)
		{
				lcd_showstr(30,i,menu[page].rowlist[i].commit);
				if (menu[page].rowlist[i].next_status == MENU_STAY)
						lcd_showint8(80,i,menu[page].rowlist[i].value);
		}
}

void display_entry(void *parameter)
{
	  //��ʾhome����
		uint8 current_page=HOME;
		page_init(current_page);
//		for (int i=0;i<7;i++)
//		{
//				lcd_showstr(30,i,home[i].commit);
//				if (home[i].next_status == MENU_STAY)
//						lcd_showint8(80,i,home[i].value);
//		}
		while(1)
		{
				//���հ�����Ϣ
				if (SpeedRB < 50 && SpeedRB > -50)
				{
						lcd_showstr(80,0,"KEY_NONE ");
						cursor.key_status=KEY_NONE;
				}
				if (SpeedRB > 50 )
				{
						lcd_showstr(80,0,"++       ");
						cursor.key_status=KEY_UP;
				}
				if (SpeedRB < -50)
				{
						lcd_showstr(80,0,"--       ");
						cursor.key_status=KEY_DOWN;
				}
				if (SpeedRF > 50)
				{
						cursor.key_status=KEY_RIGHT;
				}
				if (SpeedRF <- 50)
				{
						cursor.key_status=KEY_LEFT;
				}
				
				
				//��������Ϣ
				switch(cursor.key_status)
				{
					case KEY_DOWN:
					{
							lcd_showstr(0,cursor.row_num,"  ");
							//menu[current_page].rowlist[cursor.row_num].cursor_is_here=CURSOR_NHERE;
						  if (cursor.row_num<menu[current_page].menu_len-1)
									cursor.row_num++;
							//menu[current_page].rowlist[cursor.row_num].cursor_is_here=CURSOR_HERE;
							cursor.key_status=KEY_NONE;
							break;
					}
					case KEY_UP:
					{
							lcd_showstr(0,cursor.row_num,"  ");
							//menu[current_page].rowlist[cursor.row_num].cursor_is_here=CURSOR_NHERE;
							if (cursor.row_num>0)
								cursor.row_num--;
							//menu[current_page].rowlist[cursor.row_num].cursor_is_here=CURSOR_HERE;
							cursor.key_status=KEY_NONE;
							break;
					}
					case KEY_RIGHT:
					{
							if (menu[current_page].rowlist[cursor.row_num].next_status==MENU_STAY)
							{
									menu[current_page].rowlist[cursor.row_num].value++;
									lcd_showint8(80,cursor.row_num,menu[current_page].rowlist[cursor.row_num].value);
							}
							if (menu[current_page].rowlist[cursor.row_num].next_status==MENU_NEXT)//����û������ʱ���
							{
									current_page=menu[current_page].rowlist[cursor.row_num].next_menu;
									lcd_clear(WHITE);
									page_init(current_page);
							}
							if (menu[current_page].rowlist[cursor.row_num].next_status==MENU_FUN)
							{
									menu[current_page].rowlist[cursor.row_num].next_fun();
							}
							break;
					}
					case KEY_LEFT:
					{
							if (menu[current_page].rowlist[cursor.row_num].next_status==MENU_STAY)
							{
									menu[current_page].rowlist[cursor.row_num].value--;
									lcd_showint8(80,cursor.row_num,menu[current_page].rowlist[cursor.row_num].value);
							}
							break;
					}

				}
				//����ȷ���α�������
				lcd_showstr(0,cursor.row_num,">>");
				rt_thread_mdelay(50);
	}
}

void display_init()
{
		rt_thread_t Thdisplay;
		//�����߳�
		Thdisplay = rt_thread_create("display",display_entry,RT_NULL,4096,20,5);
	
	
		//�α��ʼ��
		cursor.key_status=0;
		cursor.row_num=0;
		if (RT_NULL != Thdisplay)
		{
				rt_thread_startup(Thdisplay);
		}

}
