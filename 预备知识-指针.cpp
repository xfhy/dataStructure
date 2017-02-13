/*
2015年8月26日19:46:40
预备知识-指针 
*/
# include <stdio.h>

int main()
{
	int *p;   //p变量只能保存 int* 类型的变量的地址 
	int i=10;
	int j;
	
	p = &i;
	j = *p;
	printf("i=%d,j=%d,*p=%d\n",i,j,*p); 
	
	int a[5] = {1,2,3,4,5}; 
	 //a[3]等价于*(a+3)        *(a+3) 访问更快 
	 
	printf("%p\n",a+1);    //a+1代表地址     
	printf("%p\n",a+2);
	printf("%p\n",a+3);
	
	return 0;
}
