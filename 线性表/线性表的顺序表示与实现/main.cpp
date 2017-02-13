# include "function.h"

int main(void)
{
	SqList L;      //定义
	InitList(L);  //初始化
	Random(L);    //赋一些初值
	/*----------------菜单设计-------------*/
	cout<<"\t---顺序表---"<<endl;
	cout<<"1.显示表内元素"<<endl;
	cout<<"2.插入"<<endl;
	cout<<"3.删除"<<endl;
	cout<<"4.查找"<<endl;
	cout<<"请选择您需要的操作(已初始化一定元素):"<<endl;
	int temp;
	cin>>temp;
	if(temp>0 && temp<=4)
	{
		switch(temp)
		{
				case 1:
					Show(L);
					break;
				case 2:
					ListInsert(L);
					break;
				case 3:
					Listdelete(L);
					break;
				case 4:
					Seek(L);
					break;
		}
	}

	system("pause");

	return 0;
}