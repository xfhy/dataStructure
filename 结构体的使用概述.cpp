/*
2015年8月27日22:21:37
结构体的使用概述 

  为了表示一些复杂的数据,而普通的基本 类型无法满足要求 
  与类相似    与类比较起来,有局限性 ,没有方法 
*/
# include <stdio.h>
# include <string.h> 

struct Student
{
	int num;
	char name[200];
	int age;
};     //分号不能省

typedef struct Student st;  

int main(void)
{
	st p1 = {8,"潇风寒月2",19};
	printf("学号:%d \n姓名:%s \n年龄:%d \n",p1.num,p1.name,p1.age); 
	p1.num=2;
	strcpy(p1.name,"潇风寒月");
	printf("学号:%d \n姓名:%s \n年龄:%d \n",p1.num,p1.name,p1.age); 
	
	return 0; 
} 
