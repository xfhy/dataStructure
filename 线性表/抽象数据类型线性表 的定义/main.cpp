/*
2015年8月29日22:03:09
抽象数据类型线性表 的定义 
*/

# include <stdio.h>
# include <malloc.h> 
# include <Windows.h>

struct Student   //学生 
{
	int num;                  //学号 
	int age;                  //年龄 
	struct Student * next;    //连接下一个的指针 
};
typedef struct Student st; 

//创建链表
st *Initlist(void)   
{
	st *h,*p,*q;     //头指针,前一个,后一个
	h = (st *)malloc( sizeof(st) );
	h->next=NULL;
	p = h;
	int num,age;
	printf("请输入学生学号,年龄(中间以逗号隔开)\n");
	scanf("%d,%d",&num,&age);
	printf("\n"); 
	while(num!=-1)
	{
		q = (st *)malloc( sizeof(st) );   //临时建立一个数组元素
		q->num=num;
		q->age=age;
		p->next = q;
		p = q;   //一步一步的向前移 
		scanf("%d,%d",&num,&age);
	} 
	p->next = '\0';   //最后那个元素是空的 
	return h; 
}   

//输出链表
void Show(st *h)
{
	st *p;   //只需要一个即可,他自己向后移动即可全部输出,知道下一个为 '\0' 
	p = h->next;
	if(p == '\0')
	{
		printf("这是空的链表!\n");
	}
	else
	{
		printf("学生信息如下:\n");
		printf("学号 年龄\n"); 
	    while(p != '\0')
		{
			printf(" %d   %d  \n",p->num,p->age);
			p = p->next;   //向后移 
		} 
    }

} 

//销毁线性表
void ClearList(st *h)
{
	st *p,*q;
	p = h->next;
	q = p->next;
	while(q!=NULL)
	{
		free(p);
		p = q;
		q = q->next;
	}
}

//判断线性表是否为空表
bool Listempty(st *h)
{
	if(h->next == NULL)   //如果我空表,则返回true
		return true;
	else
		return false;
}

//返回线性表元素个数
int ListLength(st *h)
{
	int len = 0;
	st *p;
	p = h->next;
	if(p==NULL)
	   return 0;
	else
	{
		while(p!=NULL)
		{
			len++;
			p = p->next;
		}
	}
	return len;
}

//返回线性表中第i个元素的值
int Getelem(st *h,int i,int *t)
{
	int temp=0;
	st *p;
	p = h->next;
	if(p==NULL)
	   return 0;
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp==i)
			{
				*t=p->num;
				break;
			}
			p = p->next;
		}
	}
}

//返回第一次遇到e数据元素的位序
int Locateelem(st *h,int t)
{
	int temp=0;
	st *p;
	p = h->next;
	if(p==NULL)
	   printf("哈哈,空列表\n");
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(t == p->num)
				return temp;
			p = p->next;
		}
	}
}

//在i位置之前插入元素
void Listinsert(st *h,int num,int age,int local)
{
	st *p,*q;    //前一个,后一个
	int temp = 0;
	p = h->next;
    q = p->next;
	if(p == NULL && local!=1)
	    printf("空链表\n");
	else if(local==1)
	{
		st *t = (st *)malloc(sizeof(st));
		t->num = num;
		t->age = age;
		h->next = t;
		t->next = p;
	}
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp == local-1)
			{
				st *t = (st *)malloc(sizeof(st));
				t->num = num;
				t->age = age;
				p->next = t;
				t->next = q;
				break;
			}
			p = p->next;
			if(q->next!=NULL)
			  q = q->next;
		}
	}
}

//删除第i个元素
void Listdelete(st *h,int i)
{
	st *p,*q;
	p = h->next;
	q = p->next;
	int temp=0;
	if(p==NULL)
		printf("空链表!\n");
	else
	{
		while(p!=NULL)
		{
			temp++;
			if(temp == i-1)
			{
				p->next = q->next;
			}
			p = p->next;
			q = q->next;
		}
	}
}

//根据学号排序
void Sortlist(st *h)    //只需要交换数据域就行
{
	st *p,*q;  
	st *t = (st *)malloc(sizeof(st));   //临时的结构体
	p = h->next;
	if(p==NULL)
	{
		printf("呵呵,空的链表!\n");
	}
	else
	{
		for(p=h->next; p!=NULL; p=p->next)
	   {
		   for(q=h->next; q!=NULL; q=q->next)
		   {
			   if( (p->num) < (q->num) )
			   {
				   t->num = p->num;
				   t->age = p->age;
				   p->num = q->num;
				   p->age = q->age;
				   q->num = t->num;
				   q->age = t->age;
			   }
		   }
	   }
	}
}

int main(void)
{
	st *h;   //头指针 
	h = Initlist(); 
	Show(h);
	Sortlist(h);
	//ClearList(h);
	/*bool temp = Listempty(h);
	if(temp==true)
		printf("哈哈,为空表\n");
	else
		printf("呵呵,不是空表\n");*/
	//printf("元素个数为%d\n", ListLength(h) );
	//int len = ListLength(h);  //计算长度
	//printf("请输入您想返回地几个元素的值\n");
	//int temp2,e;
	//scanf("%d",&temp2);
	//if(1 <= temp2 && temp2 <= len)
	//{
	//	Getelem(h,temp2,&e);
	//	printf("您想查找的元素的num为%d\n",e);
	//}
	//else
	//	printf("卧槽,你妹的,不再长度以内\n");

	/*printf("请输入您想查找的元素,我们将会为您返回它的位序\n");
	int temp3;
	scanf("%d",&temp3);
	int localtion;
	localtion = Locateelem(h,temp3);
	printf("您想查找的元素的位序为%d\n",localtion);*/

	/*printf("请输入需要插入的元素内容和位置(学号,年龄,位置)\n");
	int num1,age1,local1;
	scanf("%d,%d,%d",&num1,&age1,&local1);
	if(local1>=1 && local1<=len)
	  Listinsert(h,num1,age1,local1);*/

	/*printf("请输入您想要删除的元素的位置");
	int i;
	scanf("%d",&i);
	Listdelete(h,i);*/
	Show(h);

	system("pause");

	return 0; 
} 