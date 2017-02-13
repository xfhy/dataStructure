# include "comdef.h"

typedef struct
{
	ElemType *top;    //栈顶指针
	ElemType *base;  //栈的底部
	int stacksize;   //栈的大小
}SqStack;

//构造一个空栈
Status InitStack(SqStack &S)
{
	S.base = (ElemType *)malloc( (sizeof(ElemType)) * LIST_INIT_SIZE );//初始化栈的大小
	if(!S.base)  return ERROR;   //分配动态内存失败
	S.top = S.base;
	S.stacksize = LIST_INIT_SIZE;   //大小初始化为LIST_INIT_SIZE
	return OK;
}

//压栈
Status Push(SqStack &S,ElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		ElemType * newbase;
		//新建一个指针,防止原来的地址丢失
		//realloc,                        原地址,新大小
		newbase = (ElemType *)realloc( S.base,(S.stacksize+LISTINCREMENT)*sizeof(ElemType) );
		if(!newbase)  return ERROR;   //分配失败
		S.base = newbase;
		S.stacksize +=  LISTINCREMENT;
	}
	*S.top++ = e;  //等价于S.top = e;   *S.top++;     操作站顶 
	return OK;
}

//出栈
Status Pop(SqStack &S,ElemType &e)
{
	if(S.base == S.top)
		return ERROR;   //空栈
	e = *(S.top-1);
	//cout<<e<<endl;
	*S.top--;
	return OK;
}

//取出栈顶元素
Status GetTop(SqStack S,ElemType &e)
{
	e = *(S.top-1);   //最上面的是空的..第二个才是有数据的
	//cout<<e<<endl;
	return OK;
}

//栈长
int StackLength(SqStack S)
{
	return (S.top - S.base);
}

//判断栈是否为空
Status StackEmpty(SqStack S)
{
	if( S.top == S.base )
		return TRUE;
	else
		return FALSE;
}

//销毁栈
Status DestroyStack(SqStack &S)
{
	if(!S.base)
	{
	   free(S.base);
	   return OK;
	}
	else
		return ERROR;
}
