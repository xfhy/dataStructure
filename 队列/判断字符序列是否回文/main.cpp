# include "comdef.h"
# include <iostream>

using namespace std;

//初始化链表
Status InitStack(LinkStack &S)
{
	S = NULL;
	return OK;
}

//压栈
Status Push(LinkStack &S,ElemType e)
{
	/*------新建一个节点,将数据放进去-------*/
	LinkStack p; 
	p = (LinkStack)malloc( sizeof(Link) );
	if(!p)
		return ERROR;
	p->data = e;  

	p->next = S;
	S = p;
	return OK;
}

//出栈
Status Pop(LinkStack &S,ElemType &e)
{
	if(S==NULL)
		return ERROR;
	e = S->data;
	//cout<<e<<endl;
	S = S->next;
	return OK;
}

//取栈顶元素
Status GetTop(LinkStack &S,ElemType &e)
{
	if(S==NULL)
		return ERROR;
	e = S->data;
	cout<<e<<endl;
	return OK;
}

//栈的长度
int GetLength(LinkStack S)
{
	int len=0;
	LinkStack p = S;
	while(p)
	{
		p = p->next;
		len++;
	}
	return len;
}

//销毁栈
Status ClearStack(LinkStack &S)
{
	if(S==NULL)
		return ERROR;
	LinkStack p;
	while(S)
	{
		p = S;
		S = S->next;
		free(p);
	}
	return OK;
}


/*-------------------------------------------------华丽的分界线------------------------------------------------------*/

//构造一个空队列    链表
Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc( sizeof(QNode) );
	Q.front->next = NULL;
	return OK;
}

//插入元素e为Q的新的队尾元素   队列
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

//若队列不空,则删除Q的队头元素,用e返回其值   队列
//删除
Status DeQueue(LinkQueue &Q,ElemType &e)
{
	if( Q.front==Q.rear )
		return ERROR;
	QueuePtr p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	if(p==Q.rear)   //假如队列只有一个元素,则删除了第一个元素之后,Q.rear就指向的位置不正常了
		Q.rear = Q.front;   //防止Q.rear丢失
	free(p);
	//cout<<e<<endl;
	return OK;
}

//销毁队列   队列
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

//判断是否为空队列  队列
Status QueueEmpty(LinkQueue Q) 
{
	//if(头等于尾),则空,则返回OK    否则相反
	return ( Q.front==Q.rear );  
}

//返回队列元素个数   队列
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

//返回队列队头元素  链表
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
	LinkQueue L;   //链式  队列
	InitQueue(L);
	LinkStack S;
	InitStack(S);  //链式 栈
	ElemType a[3] = {1,2,2};
	for(int i=0; i<3; i++)
	{
		Push(S,a[i]);   //压栈
		EnQueue(L,a[i]);  //入队
	}
	ElemType temp1,temp2;
	bool t=true;
	for(int i=0; i<3; i++)
	{
		Pop(S,temp1);
		DeQueue(L,temp2);
		if(temp1!=temp2)
		{
			t=false;
			cout<<"不是回文数哦"<<endl;
			break;
		}
	}
	if(t==true)
	   cout<<"是回文数"<<endl;
	system("pause");
	return 0;
}