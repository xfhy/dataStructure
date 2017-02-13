# include "comdef.h"

//初始化
Status InitList(SqList &L)
{
	//只需要一个结构体
	L.elem = (ElemType *)malloc( LIST_INIT_SIZE *sizeof(ElemType) );  
	//初始化这个结构体的elem的内容,100个
	if(! L.elem)  exit(OVERFLOW);  //分配失败
	L.length = 0;                  //线性表的长度为0
	L.listsize = LIST_INIT_SIZE;   //初始化时的大小为101
	return OK;   //返回成功
}

//显示
void Show(SqList &L)
{
	//顺序表的第一个节点是不存放数据的
	for(int i=1; i<=L.length; i++)
	{
		cout<<L.elem[i]<<endl;
	}
}

//赋一些初值进去
void Random(SqList &L)
{
	for(int i = 1; i<=10; i++)
	{
		L.elem[i] = i+3;
		L.length++;
	}
}

//将数组就地倒置
Status Convert(SqList &L)
{
	int i=1,j=L.length;
	ElemType t;
	while( i<=(L.length/2) )
	{
		t = L.elem[i];
		L.elem[i] = L.elem[j];
		L.elem[j] = t;
		i++;
		j--;
	}
	return OK;
}

int main(void)
{
	SqList L;
	InitList(L);
	Random(L);
	//Show(L);
	Convert(L);
	Show(L);
	system("pause");
	return 0;
}