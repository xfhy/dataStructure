# include "comdef.h"
# include <iostream>

using namespace std;

//构造一个空队列
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc( sizeof(QNode) );
	Q.front->next = NULL;
	return OK;
}

//插入元素e为Q的新的队尾元素
//插入
Status EnQueue(LinkQueue &Q,ElemType e)
{
	QueuePtr p = (QueuePtr)malloc( sizeof(QNode) );
	p->next = NULL;  //队列尾指向NULL
	p->data = e;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

//若队列不空,则删除Q的队头元素,用e返回其值
//删除
Status DeQueue(LinkQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	QueuePtr p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if(p==Q.rear)   //假如队列只有一个元素,则删除了第一个元素之后,Q.front就指向NULL,就找不到Q.rear了,Q.rear就指向的位置不正常了
		Q.rear = Q.front;   //防止Q.rear丢失
	free(p);
	//cout<<e<<endl;
	return OK;
}

//销毁队列
Status DestroyQueue(LinkQueue &Q)
{
	if(Q.front==Q.rear)
		return ERROR;
	while(Q.front)  //从头指针开始,一直删除往后,直到最后一个
	{
		Q.rear = Q.front->next;   //将rear设置为工作变量,这样就少设一个变量
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

//判断是否为空队列
Status QueueEmpty(LinkQueue Q)
{
	//if(头等于尾),则空,则返回OK    否则相反
	return ( Q.front==Q.rear ); 
}

//返回队列元素个数
int QueueLength(LinkQueue Q)
{
	int len=0;
	while(Q.front!=Q.rear)   //当头部等于尾的时候,停止计数
	{
		Q.front = Q.front->next;
		len++;
	}
	//cout<<len<<"个元素"<<endl;
	return len;
}

//返回队列队头元素
Status GetHead(LinkQueue Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	e = Q.front->next->data;   //Q.front的下一个的data
	cout<<e<<endl;
	return OK;
}

int main(void)
{
	LinkQueue Q;
	InitQueue(Q);
	int e=0;
	EnQueue(Q,1);
	EnQueue(Q,2);
	EnQueue(Q,3);
	EnQueue(Q,4);
	QueueLength(Q);
	//DestroyQueue(Q);

	/*DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);
	DeQueue(Q,e);*/

	/*if( QueueEmpty(Q) )
		cout<<"空队列"<<endl;*/
	GetHead(Q,e);
	system("pause");
	return 0;
}