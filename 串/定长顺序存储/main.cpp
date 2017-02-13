# include "comdef.h"
# include <iostream>

using namespace std;

//输出
Status Show(SString T)
{
	for(int i=0; T[i]!='\0'; i++)
	{
		cout<<T[i]<<endl;
	}
	return OK;
}

//求字符串长度
int StrLength(SString T)
{
	int len=0;
	for(int i=0; T[i]!='\0'; i++)
	{
		len++;
	}
	return len;
}

//串连接
Status Concat(SString &T,SString S1,SString S2)
{//用T返回由S1和S2链接而成的新的串，若未截断，则返回TRUE，否则返回FLASE
	bool uncut = true;         //未分裂
	int i;
	int len1 = StrLength(S1);
	int len2 = StrLength(S2);
	if( (len1+len2)<MAXSTRLEN )
	{
		for(i=0 ; i<len1; i++)  //从S[1]开始才是有效值，到后面
		{
			T[i] = S1[i];
		}
		for(i=len1; i< len1+len2 ; i++)
		{
			T[i] = S2[i-len1];
		}
		T[len1+len2] = '\0';
		uncut = true;
	}
	else if( len1<MAXSTRLEN )
	{
		for(i=0 ; i<len1; i++)  //从S[1]开始才是有效值，到后面    先把S1中的有效值放到T中去
		{
			T[i] = S1[i];
		}
		for(i=len1; i<MAXSTRLEN; i++)
		{
			T[i] = S2[i-len1+1];
		}
		T[MAXSTRLEN] = '\0';   //MAXSTRLEN+1个位置
		uncut = false;
	}
	else  //当S1的长度等于MAXSTRLEN
	{
		for(i=0; i<MAXSTRLEN; i++)
		{
			T[i] = S1[i];
		}
		T[MAXSTRLEN] = '\0';
	}
	return OK;
}

//求子串
Status SubString(SString &T,SString S,int pos,int len)  //目标字符串，需要从中提取的字符串，起点位置，长度
{
	int lens = StrLength(S);   //求长度
	if(pos<1 || pos>lens || len<0 || len>S[0]-pos+1)
		return ERROR;
	int i,j=0,t=0;
	for(i=pos; j<len; i++)
	{
		T[t] = S[i];
		t++;
		j++;
	}
	T[t] = '\0';
	return OK;
}

//比较字符串是否相等
Status StrCompare(SString S,SString T)
{
	int len1 = StrLength(S);
	int len2 = StrLength(T),count=0;  //T的长度,长度计数
	if(len1!=len2)  //如果两个字符串长度不一致
		return -1;
	else
	{
		for(int i=0; i<len1; i++)
		{
			if(S[i]==T[i])
				count++;
		}
		if(count==len1)
			return 0;
		else if(count!=len1)
		    return -1;
	}
}

//字串是否包含   Brute-Force算法
int Index(SString S,SString T,int pos)
//T为非空串,若主串S中第pos个字符之后存在与T相等的子串,则返回第一个这样的子串在S中的位置,否则返回0
{
	//eg:   S   q w e r w e w \0
	//      T   e w \0
	if(pos>0)  //位置合法
	{
		int i=pos,len1 = StrLength(S),len2 = StrLength(T);
		SString temp = "";
		while( i<=(len1-len2+1) )  //下标在合理的范围之内
		{
			SubString(temp,S,i,len2);  //求出S中每一个字符后面的T长度的字串,来和T比较
			temp[len2] = '\0';
			if(StrCompare(temp,T)!=0)   //如果不相等,继续从i后面的那个元素开始比较 
				i++;
			else   //如果在第i个元素相等,则返回i的下标
				return i+1;   //返回第多少个元素
		}
	}
	return 0;  //否则返回0
}

int main(void)
{
	SString T="";

	/*SString S1 = "qwertyuiop";
	S1[10] = '\0';
	SString S2 = "qwe";
	S2[4] = '\0';
	Concat(T,S1,S2);
	Show(T);*/

	//SString S1 = "qwertyuiop";
	//S1[10] = '\0';   //结尾标志
	//cout<<StrLength(S1)<<endl;   10
	//Show(S1);

	/*SString S1 = "qwertyuiop";
	S1[10] = '\0';
	SubString(T,S1,1,6);
	Show(T);*/

	/*SString S1 = "abgd";
	S1[4] = '\0';
	SString S2 = "abgd";
	S2[4] = '\0';
	if( StrCompare(S1,S2) )
		cout<<"相等"<<endl;*/

	SString S1 = "qwerwew";
	S1[7] = '\0';
	SString S2 = "ew";
	S2[2] = '\0';
	if( Index(S1,S2,1) )
		cout<<"有"<<endl;

	system("pause");
	return 0;
}