# include "comdef.h"
# include"function.h"
# include <string.h>

using namespace std;


//N进制转任意(r)进制     OK
void Convertion(int N,int r)
{
	SqStack S;
   if( InitStack(S) )
		cout<<"初始化栈的顺序存储结构成功!"<<endl;
   while(N)  //压栈
   {
	   Push(S,N%r);
	   N /= r;
   }
   int e;
   while(S.base!=S.top)
   {
	   Pop(S,e);
	   if( e<=9 || e>=0)
		   cout<<e;
	   else
		   cout<<'A'+e-10;
   }
   cout<<endl;
}

////括号匹配的检验
//Status TestP(string str)
//{
//   SqStack S;
//   if( InitStack(S) )
//		cout<<"初始化栈的顺序存储结构成功!"<<endl;
//	char t;
//	int len = str.length();
//	int i=0;
//	//cout<<len<<endl;
//	while(i<len)
//	{
//		switch(str[i])
//		{
//		   case '(':
//		   case '[':
//			   Push(S,str[i]);  //遇左压栈
//			   break;
//		   case ')':
//			   if( Pop(S,t) )  //遇右出栈,出栈时判断是否与最近的括号匹配
//			   {
//				   if( t!='(' )
//					   return ERROR;
//			   }
//			   break;
//		   case ']':
//			   if( Pop(S,t) )
//			      if(t!='[')  
//					  return ERROR;
//			   break;
//		}
//		i++;
//	}
//	return OK;
//}

int main(void)
{
	SqStack S;
	if( InitStack(S) )
		cout<<"初始化栈的顺序存储结构成功!"<<endl;
	int e=-1;
	cout<<"压栈1,2,3,4"<<endl;
	Push(S,1);
	Push(S,2);
	Push(S,3);
	Push(S,4);
	cout<<"出栈4,3,2,1"<<endl;
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);
	Pop(S,e);

	//if( !Pop(S,e) )
		//cout<<"空栈"<<endl;

	/*int len = StackLength(S);
	cout<<len<<endl;*/

	/*if( !StackEmpty(S) )
		cout<<"不是空表!"<<endl;*/

	//DestroyStack(S);

	//Convertion(22,8);

	/*if( TestP("([]())") )
		cout<<"OK"<<endl;*/
	/*if( TestP("([)]") )
		cout<<"OK"<<endl;*/

	system("pause");
	return 0;
}