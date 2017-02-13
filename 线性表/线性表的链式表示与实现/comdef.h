#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //返回的状态
typedef int ElemType ;       //数据类型

typedef struct LNODE   //线性表的单链表存储结构
{
	ElemType data;   //数据域
	struct LNODE *next; //指针域
}LNODE,*LinkList;