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

typedef struct Link 
{
	ElemType data;
	struct Link *next;
}*LinkStack,Link;