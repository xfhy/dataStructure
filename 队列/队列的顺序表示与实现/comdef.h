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
#define MAXQSIZE 4    //初始化时分配的大小
#define LISTINCREMENT 10      //线性存储空间的分配增量

typedef struct      
{
	ElemType *base;  //初始化的动态分配存储空间
	int front;   //头指针,若队列不空,指向队列头元素
	int rear;   //尾指针,若队列不为空,则rear指向队尾下一个元素
}SqQueue;