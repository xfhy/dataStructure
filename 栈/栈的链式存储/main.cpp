/*
2015年10月9日20:03:43
栈的链式存储(一般不设头结点)
*/
# include "comdef.h"

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
	cout<<e<<endl;
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

int main(void)
{
	LinkStack S;
	InitStack(S);
	Push(S,1);
	Push(S,2);
	Push(S,3);
	Push(S,4);
	int e;
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	int len = GetLength(S);
	cout<<len<<endl;
	ClearStack(S);

	system("pause");
	return 0;
}