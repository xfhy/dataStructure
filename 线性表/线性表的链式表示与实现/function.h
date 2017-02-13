# include "comdef.h"
# include <iostream>

using namespace std;
int len=0;
//创建链表
LinkList Create()
{
	//头结点不存放数据
	LinkList L,p,q;
	L = (LinkList)malloc(sizeof(LNODE));
	L->next = NULL;
	q = L;
	//int len=0;
	ElemType t;
	cout<<"请输入需要初始化的元素个数"<<endl;
	cin>>len;
	cout<<"请依次输入相应元素的值"<<endl;
	for(int i=0; i<len; i++)
	{
		p = (LinkList)malloc(sizeof(LNODE));
		cin>>t;
		p->data = t;
		q->next = p;
		q = p;
	}
	q->next = NULL;   //尾结点指向NULL
	return L;
}

//输出链表
void Show(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p)
	{
		cout<<p->data<<endl;
		p = p->next;
	}
}

//当第i个元素的值存在时,其值赋给e并返回OK
Status GetElem(LinkList L,int i,ElemType &e)
{
	LinkList p = L->next;
	int j=1;
	while(p && j<i)
	{
		p = p->next;
		++j;
	}   //出循环时可能是:1.p已经是空的了(表示数组长度小于i)  2.j=i
	if(!p || j>i)   //数组长度小于i,    i值太小
		return ERROR;    //第i个元素不存在
	e = p->data;
	return OK;
}

//添加元素   指定位置
Status ListInsert(LinkList L,int i,ElemType e)
{
	LinkList p;
	p = L;
	int t=1;
	while(p && t<i)   //有可能p是空的
	{
		p = p->next;
		t++;
	}
	if(!p || t>i)   //数组长度小于i,i值太小
		return ERROR;

	LinkList t2 = (LinkList)malloc(sizeof(LNODE));
	t2->data = e;
	t2->next = p->next;  //   t2指向p的下一个
	p->next = t2;   //p指向t2
	return OK;
}

//删除元素
Status Listdelete(LinkList L,int i,ElemType &e)
{
	LinkList p,q;
	p = L;
	int j=1;
	while(p->next && j<i)   //最多循环到倒数第二个,不然下面的p = p->next会有问题
	{
		p = p->next;
		j++;
	}
	if(!p->next || j>i)
		return ERROR;
	q = p->next;
	e = q->data;   //将需要删除的元素的数据保存起来
	cout<<"删除的元素为:"<<e<<endl;
	p->next = q->next;
	free(q);
	return OK;
}

           /*-----------------将链式表就地倒置-------------------*/
//将链式表就地倒置  一
Status Convert1(LinkList &L)
{
	/*
	为了反转这个单链表，我们先让头结点的next域指向结点2，
	再让结点1的next域指向结点3，最后将结点2的next域指向结点1，
	就完成了第一次交换，顺序就变成了Header-结点2-结点1-结点3-结点4-NULL
	，然后进行相同的交换将结点3移动到结点2的前面，
	然后再将结点4移动到结点3的前面就完成了反转，思路有了，就该写代码了：
	*/
	LNODE *tmp = NULL;
	LNODE *p = NULL;
	if(L==NULL)
	{
		return ERROR; 
	}
	tmp = L->next;   //指向第二个
	
	while(tmp->next!=NULL)   //当需要换到第一个的元素不为空
	{
        p = tmp->next;    //p为tmp的下一个,也就是需要切换到第一个的元素
		tmp->next = p->next;  //让tmp指向需要需要切换到第一个的元素的下一个元素
		p->next = L->next;   //让p指向刚才的第一个元素
	    L->next = p;         //p变成第一个
	}
	
	return OK;
}

//将链式表就地倒置  二  (易懂)
Status Convert2(LinkList &L)
{
	//从链表首元素开始一直往后遍历,将遍历到的元素指向前一个元素
	LinkList p,r,q;
	p = NULL;
	q = L->next;
	while(q)    //让下一个元素指向上一个元素
	{
		r = q->next;  //r是q的下一个
		q->next = p;  //(第一次时,下一个指向新的头指针),以后每次都是下一个指向上一个元素
		p = q;        //新的链表向后移
		q = r;        //旧的链表向前移
	}
	L->next = p;
	return OK;
}

/*
假设有两个按元素值非递减次序排列的线性表，均以单链表形式存储。
编程实现将两个按元素递增有序的单链表合并为一个新的按元素递增的单链表
*/
void All(void)
{
	LinkList L1,L2,L3,p,q1,q2;   //L1,L2递增     L3递增
	L1 = (LinkList)malloc(sizeof(LNODE));
	L1->next = NULL;
	q1 = L1;
	L2 = (LinkList)malloc(sizeof(LNODE));
	L2->next = NULL;
	q2 = L2;
	/*---------------------初始化链表1---------------------*/
	for(int i=1; i<12; i++)  
	{
		if(i%3==0)
		{
		   p = (LinkList)malloc(sizeof(LNODE));
		   p->data = i;
		   q1->next = p;
		   q1 = p;
		}
	}
	q1->next = NULL;
	cout<<"L1:"<<endl;
	Show(L1);     //3   6  9
	/*---------------------初始化链表2---------------------*/
	for(int i=1; i<12; i++)
	{
		if(i%2==0)
		{
		   p = (LinkList)malloc(sizeof(LNODE));
		   p->data = i;
		   q2->next = p;
		   q2 = p;
		}
	}
	q2->next = NULL;
	cout<<"L2:"<<endl;
	Show(L2);     //4   8

	///*-----------------将两个链表变为递减的链表-------------------*/
	//Convert1(L1);   
	//Convert1(L2);

	/*-------------将两个链表合并--------------------*/
	LinkList k,head;
	head = k = (LinkList)malloc(sizeof(LNODE));   //头结点head    k是一个临时元素
	k->data = 0;
	q1 = L1->next;
	q2 = L2->next;
	while( q1 && q2 )   //当2个链表其中一个没有到最后
	{
		if( (q1->data)>=(q2->data) )  
		{
			k->next = q2;  //k指向小的那个元素   
			k = q2;        //k向后移
			q2 = q2->next; //q2也向后移
		}
		else   //同理
		{
			k->next = q1;
			k = q1;
			q1 = q1->next;
		}
	}
	k->next = q1? q1:q2;   //判断哪个链表已经是空的了,非空的链表的后面那些没有比较的元素放到k的后面
	k=head;   //完整链表构成啦,哈哈
	cout<<"合并后:"<<endl;
	Show(k);  //输出链表
}

//试编写在带头结点的单链表中删除（一个）最小值结点的（高效）算法
void DeleteOne(LinkList L)
{
	//用一个循环去找到链表的最小值,并记录最小值的前后指针
	ElemType temp;
	LinkList p,q,t1,t2;
	p = L->next;
	q = p->next;
	temp = p->data;
	while(q)
	{
		//cout<<p->data<<endl;    //输出当前正在读取的那个元素的值
		if( temp > q->data )      //找最小
		{
			temp = q->data;
			t1 = p;      //找最小元素的指针
			t2 = q;
		}
		p = p->next;              //往后移
		q = q->next;
	}
	cout<<t2->data;
	t1->next = t2->next;
	free(t2);
}

/*
设有一个带头结点的单链表，其结点的数据值均为正整数，编写完成下列功能的算法：
（1）找出最小值结点，且输出该数值；
（2）若该数值是奇数，则将其与直接后继结点的数值交换；
（3）若该数值是偶数，则将其直接后继结点删除。
*/
void Odd(LinkList L)
{
	LinkList p;
}

//	元素递增有序的单链表L,将x插入其中后仍保持L的有序性
Status  InsertX(LinkList &L,ElemType x)
{
	/*
	3种情况,   x比所有数都小,x在中间,x比所有数都大
	*/
	LinkList p,q;
	p = L->next;
	q = p->next;
	if( x<(p->data) )    //可能x比链表中所有元素都要小(升序)
	{
		LinkList e = (LinkList)malloc(sizeof(LNODE));
		e->data = x;
		L->next = e;
		e->next = p;
	}
	while(q)
	{
		if( (p->data)<=x && (q->data)>=x)   //在中间
		{
			LinkList e = (LinkList)malloc(sizeof(LNODE));
			e->data = x;
			p->next = e;
			e->next = q;
			return OK;
		}
		p = p->next;   //往后推移
		q = q->next;
	}  //出循环时,p指向最后一个元素,q指向NULL
	if( x>(p->data) )    //可能x比链表中所有元素都要大(升序)
	{
		LinkList e = (LinkList)malloc(sizeof(LNODE));
		e->data = x;
		p->next = e;
		e->next = NULL;
	}
	return OK;
}

//b）	链表是递增的 将数据值介于min和max之间的结点删除，并保持L的有序性
Status DeleteM(LinkList L,ElemType min,ElemType max)
{
	if(max<min)
		return ERROR;
	LinkList p,q,t,temp;
	p = L->next;
	q = p->next;
	while(q)  //外层循环,循序渐进,查找min在的位置
	{
		if( (q->data)>=min &&  (p->data)<=min)
		{
			t = p;   //暂时将比min小的那个节点存下来
			while( (q->data)<=max)  //出循环时,q->data大于max,   或者循环到末尾
			{
				if( (q->next)==NULL)   //当循环到末尾
				{
					t->next = NULL;
					return OK;
				}
				temp = q;     //将q的指针暂时存下来
				p = p->next;
				q = q->next;  
				free(temp);  //将之前q指向的那个节点(这个节点在min和max之间)释放
			}
			t->next = q;
			return OK;
		}
		p = p->next;
		q = q->next;
	}
	return OK;
}