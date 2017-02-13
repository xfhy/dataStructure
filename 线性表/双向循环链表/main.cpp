/*
2015年9月18日21:12:02
若d为指向表中某一节点的指针,则
d->next->prior = d->prior->next = d
d的下一个的上一个,d的上一个的下一个
*/

# include <iostream>
# include "comdef.h"

using namespace std;

typedef struct NODE    //线性表的双向链表存储结构
{
	ElemType data;
	struct NODE *prior;       //上一个
	struct NODE *next;        //下一个
}NODE,*NODELIST;

//初始化
NODELIST Initlist(void)   
{
	//动态生产头结点,前一个是自己,下一个是自己,数据为0
	NODELIST L = (NODELIST)malloc(sizeof(NODE));
	L->next = L;
	L->prior = L;
	L->data = 0;
	return L;
}

//判断链表是否为空
Status Judge(NODELIST L)  
{
	//前一个是自己时,为空
	if(L->prior==L && L->next==L)
	   return TRUE;
	else
		return FALSE;
}

//判断第i个元素是否有值
bool GetElem(NODELIST L,int i)  
{
	 int j=1;
	 NODE *q; // = (NODELIST)malloc(sizeof(NODE));      这里只需要一个指针,不需要一个空间
	 q = L->next;
	 while(j<i)
	 {
		 q = q->next;
		 j++;
	 }
	 if(i<1 || (q==L))   //当q==L时,表示i值太大,超出表的个数范围
		 return FALSE;
	 else
		 return TRUE;   //当前位置有值
}

//在表的后面添加一些元素
Status Add(NODELIST &L)
{
	int t;
	cout<<"请输入需要添加的元素个数"<<endl;
	cin>>t;
	NODELIST p;
	p = L;
	ElemType temp;
	cout<<"请输入相应的元素的值"<<endl;
	for(int i=1; i<=t; i++)
	{
		//尾插法
		cin>>temp;
       	NODELIST q = (NODELIST)malloc(sizeof(NODE));
	    q->data = temp;

		q->prior = p;
		p->next = q;
		q->next = L;
		L->prior = q;
		p = q;
	}
	return OK;
}

//显示输出
Status Show(NODELIST L)
{
	NODELIST q;
	q = L->next;
	while(q->next != L->next)
	{
		cout<<q->data<<endl;
		q = q->next;
	}
	return OK;
}

//在第i个位置添加e这个元素
Status ListInsert(NODELIST &L,int i,ElemType e)  
{
	NODE *p;
	if(i>0)
	   if(!(GetElem(L,i)))   //判断表内该地址是否有值,有值则说明i地址合法
		  return ERROR;
    if(i<1)
		return ERROR;
	p = L;    
	int j=1;
	while(j<=i)   //需要循环到插入位置的下一个位置,这样才好操作
	{
		p = p->next;
		j++;
	}    //p是需要插入的位置(q将插入)

	NODELIST q = (NODELIST)malloc(sizeof(NODE));  //新建一个结点
	q->data = e;
	//画张图,分析一下
	q->prior = p->prior;         //将q插入在p的前面一个位置,则就将p的位置替换了
	q->next = p;
	p->prior->next = q;
	p->prior = q;
	return OK;
}


//删除第i个元素的值,并将该元素的值保存到e中
Status Listdelete(NODELIST &L,int i,ElemType &e)
{
	NODELIST q;// = (NODELIST)malloc(sizeof(NODE));
	q = L;
	int j=0;
	if(i<1)
		return ERROR;
	if( !(GetElem(L,i)) )   //如果该位置没有元素
		return ERROR;
	while(j<i)
	{
		q = q->next;
		j++;
	}//出循环时:i==j    即已找到i的位置
	e = q->data;
	q->prior->next = q->next;
	q->next->prior = q->prior;
	free(q);
}

int main(void)
{
	NODELIST L;
	L = Initlist();
	Add(L);
	cout<<"------------我是分界线-----------"<<endl;
	ListInsert(L,1,6666);
	Show(L);
	cout<<"------------我是分界线-----------"<<endl;
	/*if(Judge(L))
		cout<<"是空表"<<endl;
	else
		cout<<"该表非空"<<endl;*/

	/*if(GetElem(L,2))
		cout<<"第2个元素有值"<<endl;*/

	//ListInsert(L,2,3333);
	//Show(L);

	int e=-1;
	Listdelete(L,1,e);
	Show(L);
	system("pause");
	return 0;
}