/*
2015年8月28日16:15:25
动态分配内存 
*/
# include <stdio.h>
# include <malloc.h> 
# include <time.h>
# include <stdlib.h>

int main(void)
{
	int *p;
	int len;
	printf("请输入需要申请的数组长度:");
	scanf("%d",&len); 
	p = (int *)malloc(sizeof(int)*len);    //返回第一个字节的地址 
	if(p!=NULL)       //这里NULL必须大写,不然会失败 
	{
		printf("动态数组分配成功!");
		srand(time(0));
		for(int i=0;i<len;i++)
		{
			p[i] = rand()%20;
		} 
	}
	printf("随机数组:");
	for(int i=0;i<len;i++)
	{
		printf("%4d\n",p[i]);
	}
	free(p); 
	
	return 0;
}
