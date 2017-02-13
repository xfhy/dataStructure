# include "comdef.h"
# include <iostream>

using namespace std;

//初始化
Status InitQueue(SqQueue &Q)
{
	Q.base = (ElemType *)malloc( sizeof(ElemType)*MAXQSIZE );  //初始化最初大小4
	if(!Q.base)  //判断是否分配成功
		return ERROR;
	Q.front = 0;   //开始时,无人排队
	Q.rear = 0;
	return OK;
}

//插入
Status EnQueue(SqQueue &Q,ElemType e)  //插入时只能插入MAXQSIZE-1个
{
	if( Q.front==(Q.rear+1)%MAXQSIZE )  //2种情况   rear在队头,在中间
		return ERROR;   //队列已满
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear+1)%MAXQSIZE;  
	//假如数组长度为4,下标已到达3时,则Q.rear不能自+1变成4,这样处理后,即可又返回到队首位置,
	//模拟环状
	cout<<"入队"<<e<<endl;
	return OK;
}

//删除
Status DeQueue(SqQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;  //判断是否非空
	e = Q.base[Q.front];
	cout<<"出队"<<e<<endl;
	Q.front = (Q.front+1)%MAXQSIZE;
	return OK;
}

//长度
int QueueLength(SqQueue Q)
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;   //2种情况
	return OK;
}

//销毁队列
Status DestroyQueue(SqQueue &Q)
{
	if(Q.front==Q.rear)
		return ERROR;  //空栈
	free(Q.base);
	return OK;
}

//返回队头
Status GetHead(SqQueue Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	e = Q.base[Q.front];
	cout<<"队头是"<<e<<endl;
	return OK;
}

int main(void)
{
	SqQueue Q;
	InitQueue(Q);
	ElemType e=0;
	EnQueue(Q,1);
	DeQueue(Q,e);

	EnQueue(Q,2);
	EnQueue(Q,3);
	GetHead(Q,e);
	system("pause");
	return OK;
}