# include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef int Status;          //返回的状态
typedef int ElemType ;       //数据类型
#define LIST_INIT_SIZE 100    //初始化时分配的大小
#define LISTINCREMENT 10      //线性存储空间的分配增量

typedef struct  QNode      //链式表
{
	ElemType data;          //数据域
	struct QNode *next;    //指针域,指向下一个节点
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;   //队头指针
	QueuePtr rear;    //队尾指针
}LinkQueue;


typedef struct Link   //栈
{
	ElemType data;
	struct Link *next;
}*LinkStack,Link;
