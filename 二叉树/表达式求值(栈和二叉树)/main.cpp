# include <iostream>
# include "function.h"
using namespace std;

Status Test(string str)
{
	LinkStack S;
	InitStack(S);
	char ch;
	ElemType t1=-1,t2=-1;
	
	for(int i=0; i<str.length(); i++)
	{
		ch=str[i];
		if(ch>=48 && ch<59)    //0-48  9-58     如果是数字
		{
			Push(S,ch-'0');
		}
		else          //如果是+-*/
		{
			Pop(S,t1);
			Pop(S,t2);
			switch(ch)
			{
			    case '+':
					Push(S,t2+t1);
					break;
				case '-':
					Push(S,t2-t1);
					break;
				case '*':
					Push(S,t2*t1);
					break;
				case '/':
					Push(S,t2/t1);
					break;
				default:
					cout<<"字符串有错!"<<endl;
			}
		}
	}
	Pop(S,t1);
	cout<<"结果为:"<<t1<<endl;
	return OK;
}

int main(void)
{
	                               //原式:
	string str = "1234-*+56/-";    //假设已经知道 后续二叉树 字符串
	Test(str);
	system("pause");
	return 0;
}