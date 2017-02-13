/*
2015年8月29日22:03:09
抽象数据类型线性表 的定义 
*/

# include <stdio.h>
# include <malloc.h> 

struct Student   //学生 
{
	int num;                  //学号 
	int age;                  //年龄 
	struct Student * next;    //连接下一个的指针 
};
typedef struct Student st; 

st *Initlist(void)   //创建链表 
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
		//q = s->next;
		//p = s;
		p = q;   //一步一步的向前移 
		scanf("%d,%d",&num,&age);
	} 
	p->next = '\0';   //最后那个元素是空的 
	return h; 
}

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
		printf("学号  年龄"); 
	    while(p != '\0')
		{
			printf("%d  %d  \n",p->num,p->age);
			p = p->next;   //向后移 
		} 
    }

} 

int main(void)
{
	st *h;   //头指针 
	h = Initlist(); 
	Show(h);
	
	return 0; 
} 
