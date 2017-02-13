/*
2015年8月30日22:39:41
typedef用法 
*/
# include <stdio.h>

typedef struct Student
{
	int age;
	int num;
}* PSTU,PSU;    //PSTU 等价于 struct Student *    
//PSU等价于 truct Student

int main(void)
{
	PSU st;
	PSTU ps = &st;
	ps->age = 99;
	printf("%d \n",st.age);
	
	return 0; 
} 
