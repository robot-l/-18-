#include "headfile.h"

#define KEY_NONE			0						//没有按下按键
#define KEY_ENTER			1						//按下<确定>键
#define KEY_DOWN			2						//按下<下>键
#define KEY_UP				3						//按下<上>键
#define KEY_LEFT			4						//按下<右>键
#define KEY_RIGHT			5						//按下<左>键


//游标（光标）元素
typedef struct
{
		uint8_t row_num;    //记录游标所在行下标
		uint8_t key_status; //记录按键状态
}ViewCursor;

//行元素

#define MENU_NEXT       0        //不跳转，调参
#define MENU_STAY       1        //跳转页面
#define MENU_FUN        2        //跳转函数
//#define CURSOR_HERE     0
//#define CURSOR_NHERE    1
typedef struct
{
		//uint8_t cursor_is_here;     //光标是否在这一行，CURSOR_HERE/CURSOR_NHERE
		uint8_t     next_status;      //该行按下确认键后下次显示状态,MENU_STAY/MENU_NEXT
		uint8_t     next_menu;        //跳转界面的下标
	  void       (*next_fun)(void);         //跳转函数
		char       *commit;           //该行显示字符串
		uint16_t    value;            //该行显示的值
}ViewRow;


//界面元素
typedef struct
{
		ViewRow *rowlist;     //指向该界面行数组的第一行
		uint8 menu_len;     //记录界面行元素个数
}ViewMenu;

#define ROW_LENGTH(x)			    ((uint16_t)(sizeof(x)/sizeof(ViewRow)))
#define DEFINE_MENU(x)        {x,ROW_LENGTH(x)}




void display_init();