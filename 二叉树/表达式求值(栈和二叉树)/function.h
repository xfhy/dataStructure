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
	cout<<"压栈:"<<e<<endl;
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
	cout<<"出栈:"<<e<<endl;
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