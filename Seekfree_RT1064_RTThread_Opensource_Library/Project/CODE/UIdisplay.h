#include "headfile.h"

#define KEY_NONE			0						//û�а��°���
#define KEY_ENTER			1						//����<ȷ��>��
#define KEY_DOWN			2						//����<��>��
#define KEY_UP				3						//����<��>��
#define KEY_LEFT			4						//����<��>��
#define KEY_RIGHT			5						//����<��>��


//�α꣨��꣩Ԫ��
typedef struct
{
		uint8_t row_num;    //��¼�α��������±�
		uint8_t key_status; //��¼����״̬
}ViewCursor;

//��Ԫ��

#define MENU_NEXT       0        //����ת������
#define MENU_STAY       1        //��תҳ��
#define MENU_FUN        2        //��ת����
//#define CURSOR_HERE     0
//#define CURSOR_NHERE    1
typedef struct
{
		//uint8_t cursor_is_here;     //����Ƿ�����һ�У�CURSOR_HERE/CURSOR_NHERE
		uint8_t     next_status;      //���а���ȷ�ϼ����´���ʾ״̬,MENU_STAY/MENU_NEXT
		uint8_t     next_menu;        //��ת������±�
	  void       (*next_fun)(void);         //��ת����
		char       *commit;           //������ʾ�ַ���
		uint16_t    value;            //������ʾ��ֵ
}ViewRow;


//����Ԫ��
typedef struct
{
		ViewRow *rowlist;     //ָ��ý���������ĵ�һ��
		uint8 menu_len;     //��¼������Ԫ�ظ���
}ViewMenu;

#define ROW_LENGTH(x)			    ((uint16_t)(sizeof(x)/sizeof(ViewRow)))
#define DEFINE_MENU(x)        {x,ROW_LENGTH(x)}




void display_init();