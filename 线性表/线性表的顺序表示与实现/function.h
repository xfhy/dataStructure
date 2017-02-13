# include "comdef.h"
# include <iostream>

using namespace std;

//初始化
Status InitList(SqList &L)
{
	//只需要一个结构体
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE *sizeof(ElemType) );  
	//初始化这个结构体的elem的内容,100个
	if(! L.elem)  exit(OVERFLOW);  //分配失败
	L.length = 0;                  //线性表的长度为0
	L.listsize = LIST_INIT_SIZE;   //初始化时的大小为100
	return OK;   //返回成功
}

//显示
void Show(SqList &L)
{
	cout<<"---------------我是分割线--------------"<<endl;
	for(int i=0; i<L.length; i++)
	{
		cout<<L.elem[i]<<endl;
	}
}

//赋一些初值进去
void Random(SqList &L)
{
	for(int i = 0; i<10; i++)
	{
		L.elem[i] = i+3;
		L.length++;
	}
}

//插入函数   在顺序表L中第i个位置之前插入新的元素e
//Status ListInsert(SqList &L,int i,ElemType e)
Status ListInsert(SqList &L)  //为了配合菜单功能的实现
{
	cout<<"需要在i个位置之前插入新的元素e,so.....请输入i,e"<<endl;
	int i;
	ElemType e;
	cin>>i>>e;
	if(i<1 || i>L.length+1)   //i的位置不对
		return ERROR;
	if(L.length >= L.listsize)    //当前存储空间已满,需要增加新分配
	{
		ElemType *newbase;   //防止分配时失误,先分配到这里
		//将原有数据从头到尾拷贝到新分配的内存区域内,并返回地址
		newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)                    //分配失败
			exit(0);     
		L.elem = newbase;              //新基址
		L.listsize +=LISTINCREMENT;    //增加存储容量
	}
	ElemType  *q = &(L.elem[L.length-1]);    //把最后那个元素的地址存入q
	for(int j = L.length-1; j>=i-1; j--)   //从最后那个元素开始,直到第i个元素,全部往后移一位
	{
		*(q+1) = *q;  
		q--;
	}
	L.elem[i-1] = e;      //将需要插入的元素赋值到底i个元素
	L.length++;           //线性表长度+1
	cout<<"插入完成之后效果如下:"<<endl;
	Show(L);
	return OK;
}

//删除函数   将需要删除的元素放到e中去
//Status Listdelete(SqList &L,int i,ElemType &e)
Status Listdelete(SqList &L)
{
	int i;
	ElemType e;
	cout<<"需要在第i个位置删除元素,so.....请输入i"<<endl;
	cin>>i;
	if(i<1 || i>L.length)
		return ERROR;
	e = L.elem[i-1];   //将需要删除的元素的值暂时保存起来
	ElemType *q = &(L.elem[i-1]);   //从需要删除的那个元素开始,一直到最后那个元素,往前移一位
	for(int j=i-1; j<L.length-1; j++)
	{
		*q = *(q+1);   //直接向前覆盖
		q++;
	}
	L.length--;   //长度减一 
	cout<<"您已经删除的元素为"<<e<<endl;
	cout<<"删除后线性表内容如下:"<<endl;
	Show(L);
	return OK;
}

//查找函数   找到后直接返回下标
//int Seek(SqList L,ElemType e)
int Seek(SqList L)
{
	ElemType e;
	cout<<"请输入需要查找的元素"<<endl;
	cin>>e;
	int len=L.length,i=0;
	while(i<=len)
	{
		if( e == L.elem[i] )
		{
			cout<<"找到元素啦,下标为"<<i<<endl;
			return i;   //找到了e,返回下标
		}
		i++;
	}
	if( i==(len+1) )
		cout<<"哈哈,并没有找到您想查找的元素"<<endl;
	return -1;   //没有找到相应的e
}