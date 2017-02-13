/*
2015年9月17日14:18:05
栈和堆的综合例子 
*/
# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

void push(int);
int pop();
int *pi,*tos;

void push(int i)    //压栈 
{
	pi++;    //先进去的数值放在栈底 
	if(pi == (tos+50))
	{
		//printf("stack overflow\n");
		printf("不能再压栈啦,已经到栈顶端咯"); 
		exit(0);
	}
	*pi = i;
}

int pop()  //出栈 
{
	if(pi == tos)   //判断是否到达栈的低端 
	{
		//printf("stack underflow\n");
		printf("已经到达栈的地步啦\n"); 
		exit(0);
	}
	pi--;
	return *(pi+1);    //这里返回pi+1,是因为上面pi的地址已经减1了 
}

int main(void)
{
	int v;
	pi = (int *)malloc(50*sizeof(int));   //动态分配50个int内存 
	if(!pi)
	{
		printf("分配失败,程序退出!\n");
		exit(0);
	}
	tos = pi;
	do
	{
		printf("请输入值,压栈   输入0就出栈  输入-1就停止");
		scanf("%d",&v);
		if(v!=0)     //当输入的值部位0,就压栈 
		   push(v);
		else         //输入0,出栈 
		   printf("pop this is it %d\n",pop());
	}while(v!=-1);
	
	return 0;
} 
